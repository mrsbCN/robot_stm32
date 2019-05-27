#ifndef __MAILBOX
#define __MAILBOX
#include <rtthread.h>
#include "ringbuffer.h"
#define EVENT_PER (1 << 0)		//Ã¿´Î
#define EVENT_FLAG2 (1 << 1)

#define EVENT_DONE_LEFT (1<<2)
#define EVENT_DONE_RIGHT (1<<3)
#define EVENT_DONE_SEE (1<<4)

#define EVENT_DIST (1 << 5)
#endif

extern struct rt_ringbuffer s_cur_rb[];
extern struct rt_mailbox  s_tar_mb[],ele_mb[],total_mb[],dis_tar_mb[];
extern struct rt_event event_per,event_done,event_dist;
extern struct rt_messagequeue sdcard_mq;
extern struct rt_mutex mission_mu;
