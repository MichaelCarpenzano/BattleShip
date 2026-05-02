#include "psp_os_event.h"

#if defined(PLATFORM_PSP)
#include <osint.h>

extern __OSEventState __osEventStateTab[OS_NUM_EVENTS];
_Static_assert(OS_NUM_EVENTS > OS_EVENT_COUNTER, "PSP shim assumes standard libultra event table layout.");

void psp_os_set_event_mesg(OSEvent event, OSMesgQueue* mq, OSMesg msg) {
    if ((u32)event >= OS_NUM_EVENTS) {
        return;
    }
    __osEventStateTab[event].messageQueue = mq;
    __osEventStateTab[event].message = msg;
}

void psp_os_dispatch_event(OSEvent event) {
    if ((u32)event >= OS_NUM_EVENTS) {
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
