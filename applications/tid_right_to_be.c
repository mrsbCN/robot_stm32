#include "tid_right_to_be.h"

void tid_right_to_be_entry(void *par)
{
    rt_mutex_take(&mission_mu, RT_WAITING_FOREVER);
    rt_uint32_t recved;

	rt_thread_mdelay(100);
    forward(right3_to_right1, right3_to_right1); //前进
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }

    for_turnright(dis_for_tri_left45, dis_for_tri_left45);//圆弧右转45
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done2:%d,time:%d\n", recved, (rt_tick_get()));
    }

    forward(right1_to_be, right1_to_be); //前进
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done3:%d,time:%d\n", recved, (rt_tick_get()));
    }

    stop();
    rt_mutex_release(&mission_mu);
}

void right_to_be_init(void)
{
    tid_right_to_be = rt_thread_create("tid_right_to_be",
                                   tid_right_to_be_entry, RT_NULL,
                                   2048 ,
                                   12 , 10);
    if(tid_right_to_be != RT_NULL)
        rt_thread_startup(tid_right_to_be);
}
