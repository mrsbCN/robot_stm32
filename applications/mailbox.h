#ifndef __MAILBOX
#define __MAILBOX
#include <rtthread.h>
#include "ringbuffer.h"
#define EVENT_PER (1 << 0)		//每次
#define EVENT_FLAG2 (1 << 1)

#define EVENT_DONE_LEFT (1<<2)
#define EVENT_DONE_RIGHT (1<<3)
#define EVENT_DONE_SEE (1<<4)

#define EVENT_DIST (1 << 5)//计算距离时间
#define EVENT_PWM_LEFT (1 << 6)//左舵机
#define EVENT_PWM_RIGHT (1 << 7)//右舵机
#define EVENT_PWM_CAM (1 << 8)//摄像头舵机

#define EVENT_PATIENT (1<<9)
#endif

extern struct rt_ringbuffer s_cur_rb[];
extern struct rt_mailbox  s_tar_mb[],ele_mb[],total_mb[],dis_tar_mb[];
extern struct rt_event event_per,event_done,event_dist,event_pwm,event_patient,event_test;
extern struct rt_messagequeue sdcard_mq;
extern struct rt_mutex mission_mu;
