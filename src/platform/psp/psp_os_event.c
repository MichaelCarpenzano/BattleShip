#include "psp_os_event.h"

#if defined(PLATFORM_PSP)
#include <PR/os_internal.h>
#include <pspdebug.h>

extern __OSEventState __osEventStateTab[OS_NUM_EVENTS];
_Static_assert(OS_NUM_EVENTS > OS_EVENT_COUNTER, "PSP shim assumes standard libultra event table layout.");

void psp_os_set_event_mesg(OSEvent event, OSMesgQueue* mq, OSMesg msg) {
    if ((u32)event >= OS_NUM_EVENTS) {
#ifdef _DEBUG
        pspDebugScreenPrintf("PSP shim: invalid event %d\n", event);
#endif
        return;
    }
    __osEventStateTab[event].messageQueue = mq;
    __osEventStateTab[event].message = msg;
#ifdef _DEBUG
    if (event != OS_EVENT_VI && event != OS_EVENT_COUNTER && event != OS_EVENT_PI && event != OS_EVENT_SI &&
        event != OS_EVENT_SP && event != OS_EVENT_DP) {
        pspDebugScreenPrintf("PSP shim: event %d registered; verify backend dispatch support\n", event);
    }
#endif
}

void psp_os_dispatch_event(OSEvent event) {
    if ((u32)event >= OS_NUM_EVENTS) {
#ifdef _DEBUG
        pspDebugScreenPrintf("PSP shim: unimplemented event %d\n", event);
#endif
        return;
    }
    __OSEventState* es = &__osEventStateTab[event];
    if (es->messageQueue != NULL) {
        osSendMesg(es->messageQueue, es->message, OS_MESG_NOBLOCK);
    }
}
#else
void psp_os_event_backend_unused(void) {}
#endif
