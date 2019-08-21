#include "tid_left_to_right.h"

void tid_left_to_right_entry(void *par)
{
    rt_mutex_take(&mission_mu, RT_WAITING_FOREVER);
    rt_uint32_t recved;

	rt_thread_mdelay(10);
	
	big_turnleft(dis_big_tlf_left, dis_big_tlf_right,0,0); //大圆
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	   
    stop();
	rt_event_send(&event_pwm,EVENT_PWM_RIGHT);
	wait_for_patient();
	if (RT_EOK == rt_event_recv(&event_patient, EVENT_PATIENT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("patient let me go.\n");
    }
	rt_event_send(&event_pwm,EVENT_PWM_RIGHT);
	
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
