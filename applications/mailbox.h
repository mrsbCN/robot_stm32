#include <rtthread.h>
#include "ringbuffer.h"
#define EVENT_FLAG1 (1 << 1)
#define EVENT_FLAG2 (1 << 2)

#define EVENT_DONE_LEFT (1<<1)
#define EVENT_DONE_RIGHT (1<<2)
#define EVENT_DONE_SEE (1<<3)


extern struct rt_ringbuffer s_cur_rb[];
extern struct rt_mailbox  s_tar_mb[],ele_mb[],total_mb[];
extern struct rt_event event_dist,event_done;
extern struct rt_messagequeue sdcard_mq;
