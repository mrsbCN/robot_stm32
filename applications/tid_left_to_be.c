#include "tid_left_to_be.h"

void tid_left_to_be_entry(void *par)
{
    rt_mutex_take(&mission_mu, RT_WAITING_FOREVER);
    rt_uint32_t recved;
	rt_thread_mdelay(10);
	
    forward(loc_left6_x,loc_left6_y,spd_for_left,spd_for_right); //前进
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	forward(loc_left5_x,loc_left5_y,spd_for_left,spd_for_right); //前进
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	forward(loc_left4_x,loc_left4_y,spd_for_left,spd_for_right); //前进
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
    forward(loc_left3_x,loc_left3_y,spd_for_left,spd_for_right); //前进
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	forward(loc_left2_x,loc_left2_y,spd_for_left,spd_for_right); //前进
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	forward(loc_begin_x,loc_begin_y,spd_for_left,spd_for_right); //前进
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
    stop();
    rt_mutex_release(&mission_mu);
}

void left_to_be_init(void)
{
    tid_left_to_be = rt_thread_create("tid_left_to_be",
                                   tid_left_to_be_entry, RT_NULL,
                                   2048 ,
                                   12 , 10);
    if(tid_left_to_be != RT_NULL)
        rt_thread_startup(tid_left_to_be);
}
