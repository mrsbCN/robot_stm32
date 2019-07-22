#include "tid_left_to_right.h"

void tid_left_to_right_entry(void *par)
{
    rt_mutex_take(&mission_mu, RT_WAITING_FOREVER);
    rt_uint32_t recved;

	rt_thread_mdelay(100);
    backward(left3_to_left2, left3_to_left2); //后退
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }

    back_turnleft(dis_back_tlf_left, dis_back_tlf_right);//左转
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done2:%d,time:%d\n", recved, (rt_tick_get()));
    }

    backward(left2_to_right2, left2_to_right2);//后退
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done3:%d,time:%d\n", recved, (rt_tick_get()));
    }

    back_turnleft(dis_back_tlf_left, dis_back_tlf_right);//左转
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done5:%d,time:%d\n", recved, (rt_tick_get()));
    }
    
    backward(right2_to_right3, right2_to_right3);//后退
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done5:%d,time:%d\n", recved, (rt_tick_get()));
    }
    
    stop();
    rt_mutex_release(&mission_mu);
}

void left_to_right_init(void)
{
    tid_left_to_right = rt_thread_create("tid_left_to_right",
                                   tid_left_to_right_entry, RT_NULL,
                                   2048 ,
                                   12 , 10);
    if(tid_left_to_right != RT_NULL)
        rt_thread_startup(tid_left_to_right);
}
