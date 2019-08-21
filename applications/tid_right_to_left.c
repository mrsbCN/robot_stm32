#include "tid_right_to_left.h"

void tid_right_to_left_entry(void *par)
{
    rt_mutex_take(&mission_mu, RT_WAITING_FOREVER);
    rt_uint32_t recved;

	rt_thread_mdelay(10);
	big_turnright(dis_big_tri_left,dis_big_tri_right,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
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

void right_to_left_init(void)
{
    tid_right_to_left = rt_thread_create("tid_right_to_left",
                                   tid_right_to_left_entry, RT_NULL,
                                   2048 ,
                                   12 , 10);
    if(tid_right_to_left != RT_NULL)
        rt_thread_startup(tid_right_to_left);
}
