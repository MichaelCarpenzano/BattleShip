#pragma once

#include <PR/os.h>

void psp_os_set_event_mesg(OSEvent event, OSMesgQueue* mq, OSMesg msg);
void psp_os_dispatch_event(OSEvent event);
