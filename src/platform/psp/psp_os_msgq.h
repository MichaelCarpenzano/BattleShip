#pragma once

#include <PR/os.h>

void psp_os_create_mesg_queue(OSMesgQueue* mq, OSMesg* msg, s32 msgCount);
s32 psp_os_send_mesg(OSMesgQueue* mq, OSMesg msg, s32 flags);
s32 psp_os_recv_mesg(OSMesgQueue* mq, OSMesg* msg, s32 flags);
