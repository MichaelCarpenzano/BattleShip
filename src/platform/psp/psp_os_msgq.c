#include "psp_os_msgq.h"

#if defined(PLATFORM_PSP)
#include <pspkernel.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    OSMesgQueue* mq;
    SceUID semFree;
    SceUID semUsed;
} PSPOSMesgQueueState;

static PSPOSMesgQueueState sPSPMsgQState[64];
static s32 sPSPMsgQCount = 0;

static PSPOSMesgQueueState* psp_os_get_state(OSMesgQueue* mq) {
    for (s32 i = 0; i < sPSPMsgQCount; i++) {
        if (sPSPMsgQState[i].mq == mq) {
            return &sPSPMsgQState[i];
        }
    }
    if (sPSPMsgQCount >= (s32)(sizeof(sPSPMsgQState) / sizeof(sPSPMsgQState[0]))) {
        return NULL;
    }
    PSPOSMesgQueueState* st = &sPSPMsgQState[sPSPMsgQCount++];
    memset(st, 0, sizeof(*st));
    st->mq = mq;
    return st;
}

void psp_os_create_mesg_queue(OSMesgQueue* mq, OSMesg* msg, s32 msgCount) {
    PSPOSMesgQueueState* st = psp_os_get_state(mq);
    mq->validCount = 0;
    mq->first = 0;
    mq->msgCount = msgCount;
    mq->msg = msg;
    if (st != NULL) {
        char semName[32];
        snprintf(semName, sizeof(semName), "ssb64_mqf_%p", (void*)mq);
        st->semFree = sceKernelCreateSema(semName, 0, msgCount, msgCount, NULL);
        snprintf(semName, sizeof(semName), "ssb64_mqu_%p", (void*)mq);
        st->semUsed = sceKernelCreateSema(semName, 0, 0, msgCount, NULL);
    }
}

s32 psp_os_send_mesg(OSMesgQueue* mq, OSMesg msg, s32 flags) {
    PSPOSMesgQueueState* st = psp_os_get_state(mq);
    if (st == NULL) return -1;
    if (flags == OS_MESG_BLOCK) sceKernelWaitSema(st->semFree, 1, NULL);
    else if (sceKernelPollSema(st->semFree, 1) < 0) return -1;
    mq->msg[(mq->first + mq->validCount) % mq->msgCount] = msg;
    mq->validCount++;
    sceKernelSignalSema(st->semUsed, 1);
    return 0;
}

s32 psp_os_recv_mesg(OSMesgQueue* mq, OSMesg* msg, s32 flags) {
    PSPOSMesgQueueState* st = psp_os_get_state(mq);
    if (st == NULL) return -1;
    if (flags == OS_MESG_BLOCK) sceKernelWaitSema(st->semUsed, 1, NULL);
    else if (sceKernelPollSema(st->semUsed, 1) < 0) return -1;
    if (msg != NULL) *msg = mq->msg[mq->first];
    mq->first = (mq->first + 1) % mq->msgCount;
    mq->validCount--;
    sceKernelSignalSema(st->semFree, 1);
    return 0;
}
#else
void psp_os_msgq_backend_unused(void) {}
#endif
