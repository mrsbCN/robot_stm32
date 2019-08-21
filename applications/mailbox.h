#ifndef __MAILBOX
#define __MAILBOX
#include <rtthread.h>
#include "ringbuffer.h"
#define EVENT_PER (1 << 0)		//ÿ��
#define EVENT_FLAG2 (1 << 1)

#define EVENT_DONE (1<<2)

#define EVENT_DIST_TURN (1<<3)
#define EVENT_DIST_FOR (1<<4)//��������¼� ǰ����
#define EVENT_DIST_BACK (1 << 5)//��������¼� ������

#define EVENT_FOR (1<<5)		//����cal�̣߳�+-90����
#define EVENT_BACK (1 << 6)
#define EVENT_TURN (1 << 7)
//#define EVENT_BACK_TURN (1 << 8)

#define EVENT_PWM_LEFT (1 << 9)//����
#define EVENT_PWM_RIGHT (1 << 10)//�Ҷ��
#define EVENT_PWM_CAM (1 << 11)//����ͷ���

#define EVENT_PATIENT (1<<12)
struct rx_msg
{
    rt_device_t dev;
    rt_size_t size;
};
#endif

extern struct rt_ringbuffer s_cur_rb[];
extern struct rt_mailbox  s_tar_mb[],dis_tar_mb[],loc_now_mb[],s_kf_mb[],s_error,angle_to_use,dist_err_mb,s_nx_mb[];
extern struct rt_event event_per,event_done,event_loca,event_pwm,event_patient,event_test;
extern struct rt_messagequeue sdcard_mq,uart_mq,rx_mq;
extern struct rt_mutex mission_mu;
