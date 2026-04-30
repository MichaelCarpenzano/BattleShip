#pragma once

#include <PR/os.h>

void psp_os_create_thread(OSThread* t, OSId id, void (*entry)(void*), void* arg, void* sp, OSPri pri);
