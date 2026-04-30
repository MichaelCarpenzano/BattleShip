#include <PR/os_internal.h>
#include <PR/ultraerror.h>
#include <osint.h>
#if defined(PLATFORM_PSP)
#include "platform/psp/psp_os_msgq.h"
#endif

s32 osSendMesg(OSMesgQueue* mq, OSMesg msg, s32 flags) {
#if defined(PLATFORM_PSP)
	return psp_os_send_mesg(mq, msg, flags);
#endif
	register u32 saveMask;
	register s32 last;

#ifdef _DEBUG
	if ((flags != OS_MESG_NOBLOCK) && (flags != OS_MESG_BLOCK)) {
		__osError(ERR_OSSENDMESG, 1, flags);
		return -1;
	}
#endif

	saveMask = __osDisableInt();

	while (MQ_IS_FULL(mq)) {
		if (flags == OS_MESG_BLOCK) {
			__osRunningThread->state = OS_STATE_WAITING;
			__osEnqueueAndYield(&mq->fullqueue);
		} else {
			__osRestoreInt(saveMask);
			return -1;
		}
	}

	last = (mq->first + mq->validCount) % mq->msgCount;
	mq->msg[last] = msg;
	mq->validCount++;

	if (mq->mtqueue->next != NULL) {
		osStartThread(__osPopThread(&mq->mtqueue));
	}

	__osRestoreInt(saveMask);
	return 0;
}
