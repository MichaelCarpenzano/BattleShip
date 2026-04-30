#include <macros.h>
#include <PR/os_internal.h>
#include <PR/ultraerror.h>
#include <osint.h>
#if defined(PLATFORM_PSP)
#include "platform/psp/psp_os_event.h"
#endif

__OSEventState __osEventStateTab[OS_NUM_EVENTS] ALIGNED(8);

void osSetEventMesg(OSEvent event, OSMesgQueue* mq, OSMesg msg) {
#if defined(PLATFORM_PSP)
    psp_os_set_event_mesg(event, mq, msg);
    return;
#endif
    register u32 saveMask;
    __OSEventState* es;

    saveMask = __osDisableInt();
    es = &__osEventStateTab[event];
    es->messageQueue = mq;
	es->message = msg;
    __osRestoreInt(saveMask);
}
