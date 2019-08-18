#include "tid_to_left.h"

void tid_to_left_entry(void *par)
{
    rt_mutex_take(&mission_mu, RT_WAITING_FOREVER);
    rt_uint32_t recved;
	
	turnleft(30,30);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop();
		rt_thread_mdelay(200);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	forward(1835,1989);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done2:%d,time:%d\n", recved, (rt_tick_get()));
    }
	for_turnright(30,30);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done3:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
    forward(1250,5100);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done4:%d,time:%d\n", recved, (rt_tick_get()));
    }
	stop();
	rt_event_send(&event_pwm,EVENT_PWM_LEFT);
	wait_for_patient();
	if (RT_EOK == rt_event_recv(&event_patient, EVENT_PATIENT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("patient let me go.\n");
    }
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
