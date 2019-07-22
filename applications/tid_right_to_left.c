#include "tid_right_to_left.h"

void tid_right_to_left_entry(void *par)
{
    rt_mutex_take(&mission_mu, RT_WAITING_FOREVER);
    rt_uint32_t recved;

	rt_thread_mdelay(100);
    backward(right3_to_right2, right3_to_right2); //后退
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }

    back_turnright(dis_back_tri_left, dis_back_tri_right);//右转
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done2:%d,time:%d\n", recved, (rt_tick_get()));
    }

    backward(right2_to_left2, right2_to_left2);//后退
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done3:%d,time:%d\n", recved, (rt_tick_get()));
    }

    back_turnright(dis_back_tri_left, dis_back_tri_right);//右转
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done5:%d,time:%d\n", recved, (rt_tick_get()));
    }
    
    backward(left2_to_left3, left2_to_left3);//后退
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done5:%d,time:%d\n", recved, (rt_tick_get()));
    }
    
    stop();
    rt_mutex_release(&mission_mu);
}

void right_to_left_init(void)
{
    tid_right_to_left = rt_thread_create("tid_right_to_left",
                                   tid_right_to_left_entry, RT_NULL,
                                   2048 ,
                                   12 , 10);
    if(tid_right_to_left != RT_NULL)
        rt_thread_startup(tid_right_to_left);
}
