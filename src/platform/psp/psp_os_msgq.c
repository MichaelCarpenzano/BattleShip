#include "psp_os_msgq.h"

#if defined(PLATFORM_PSP)
#include <string.h>

void psp_os_create_mesg_queue(OSMesgQueue* mq, OSMesg* msg, s32 msgCount) {
    if ((mq == NULL) || (msg == NULL) || (msgCount <= 0)) {
        return;
    }
    memset(mq, 0, sizeof(*mq));
    mq->validCount = 0;
    mq->first = 0;
    mq->msgCount = msgCount;
    mq->msg = msg;
}

s32 psp_os_send_mesg(OSMesgQueue* mq, OSMesg msg, s32 flags) {
    (void)flags;
    if ((mq == NULL) || (mq->msg == NULL) || (mq->msgCount <= 0)) {
        return -1;
    }
    if (mq->validCount >= mq->msgCount) {
        return -1;
    }
    mq->msg[(mq->first + mq->validCount) % mq->msgCount] = msg;
    mq->validCount++;
    return 0;
}

s32 psp_os_recv_mesg(OSMesgQueue* mq, OSMesg* msg, s32 flags) {
    (void)flags;
    if ((mq == NULL) || (mq->msg == NULL) || (mq->msgCount <= 0)) {
        return -1;
    }
    if (mq->validCount <= 0) {
        return -1;
    }
    if (msg != NULL) *msg = mq->msg[mq->first];
    mq->first = (mq->first + 1) % mq->msgCount;
    mq->validCount--;
    return 0;
}
#else
void psp_os_msgq_backend_unused(void) {}
#endif
