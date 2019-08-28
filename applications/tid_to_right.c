#include "tid_to_right.h"

void tid_to_right_entry(void *par)
{
    rt_mutex_take(&mission_mu, RT_WAITING_FOREVER);
    rt_uint32_t recved;	
	stop();
	rt_thread_mdelay(20);
	
	turnright(-45,-45,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_for();
		rt_thread_mdelay(200);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	forward(loc_right2_x,loc_right2_y,spd_for_left,spd_for_right);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done2:%d,time:%d\n", recved, (rt_tick_get()));
    }
	forward(loc_right3_x,loc_right3_y,spd_for_left,spd_for_right);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done3:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
    forward(loc_right4_x,loc_right4_y,spd_for_left,spd_for_right);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done4:%d,time:%d\n", recved, (rt_tick_get()));
    }
	forward(loc_right5_x,loc_right5_y,spd_for_left,spd_for_right);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done4:%d,time:%d\n", recved, (rt_tick_get()));
    }
	forward(loc_right6_x,loc_right6_y,spd_for_left,spd_for_right);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done4:%d,time:%d\n", recved, (rt_tick_get()));
    }
	forward(loc_right_done_x+120,loc_right_done_y-60,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done4:%d,time:%d\n", recved, (rt_tick_get()));
    }
	stop();
	rt_event_send(&event_pwm,EVENT_PWM_RIGHT);
	wait_for_patient();
	rt_event_send(&event_pwm,EVENT_PWM_RIGHT);
    rt_mutex_release(&mission_mu);
}

void to_right_init(void)
{
    tid_to_right = rt_thread_create("tid_to_right",
                                   tid_to_right_entry, RT_NULL,
                                   2048 ,
                                   12 , 10);
    if(tid_to_right != RT_NULL)
        rt_thread_startup(tid_to_right);
}
