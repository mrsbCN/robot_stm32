#include "tid_to_left.h"

void tid_to_left_entry(void *par)
{
    rt_mutex_take(&mission_mu, RT_WAITING_FOREVER);
    rt_uint32_t recved;

	rt_thread_mdelay(100);	
    turnleft(dis_tlf_left, dis_tlf_right); //左转45度
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }

    forward(be_to_left1, be_to_left1);//前进
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done2:%d,time:%d\n", recved, (rt_tick_get()));
    }

    for_turnright(dis_for_tri_left45, dis_for_tri_right45);//圆弧右转45
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done3:%d,time:%d\n", recved, (rt_tick_get()));
    }

    forward(left1_to_left3, left1_to_left3);//前进
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done5:%d,time:%d\n", recved, (rt_tick_get()));
    }
    stop();
	
	rt_event_send(&event_pwm,EVENT_PWM_LEFT);
	rt_thread_mdelay(1000);//等待加入按钮
	rt_event_send(&event_pwm,EVENT_PWM_LEFT);
    rt_mutex_release(&mission_mu);
}

void to_left_init(void)
{
    tid_to_left = rt_thread_create("tid_to_left",
                                   tid_to_left_entry, RT_NULL,
                                   2048 ,
                                   12 , 10);
    if(tid_to_left != RT_NULL)
        rt_thread_startup(tid_to_left);
}
