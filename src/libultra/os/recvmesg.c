#include <PR/os_internal.h>
#include <PR/ultraerror.h>
#include <osint.h>
#if defined(PLATFORM_PSP)
#include "platform/psp/psp_os_msgq.h"
#endif

s32 osRecvMesg(OSMesgQueue* mq, OSMesg* msg, s32 flags) {
#if defined(PLATFORM_PSP)
	return psp_os_recv_mesg(mq, msg, flags);
#endif
	register u32 saveMask;

#ifdef _DEBUG
	if ((flags != OS_MESG_NOBLOCK) && (flags != OS_MESG_BLOCK)) {
		__osError(ERR_OSRECVMESG, 1, flags);
		return -1;
	}
#endif

	saveMask = __osDisableInt();

	while (MQ_IS_EMPTY(mq)) {
		if (flags == OS_MESG_NOBLOCK) {
			__osRestoreInt(saveMask);
			return -1;
		} else {
			__osRunningThread->state = OS_STATE_WAITING;
			__osEnqueueAndYield(&mq->mtqueue);
		}
	}

	if (msg != NULL) {
		*msg = mq->msg[mq->first];
	}

	mq->first = (mq->first + 1) % mq->msgCount;
	mq->validCount--;

	if (mq->fullqueue->next != NULL) {
		osStartThread(__osPopThread(&mq->fullqueue));
	}

	__osRestoreInt(saveMask);
	return 0;
}
