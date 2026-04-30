#include "psp_os_thread.h"

#if defined(PLATFORM_PSP)
#include <string.h>

void psp_os_create_thread(OSThread* t, OSId id, void (*entry)(void*), void* arg, void* sp, OSPri pri) {
    memset(t, 0, sizeof(*t));
    t->id = id;
    t->priority = pri;
    t->context.pc = (u32)entry;
    t->context.a0 = (s64)(s32)arg;
    t->context.sp = (s64)(s32)sp - 16;
    t->state = OS_STATE_STOPPED;
}
#else
void psp_os_thread_backend_unused(void) {}
#endif
