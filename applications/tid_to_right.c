#include "tid_to_right.h"

void tid_to_right_entry(void *par)
{
    rt_mutex_take(&mission_mu, RT_WAITING_FOREVER);
    rt_uint32_t recved;

	rt_thread_mdelay(100);
    turnright(dis_tri_left, dis_tri_right,0,0); //右转45度
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop();
		rt_thread_mdelay(100);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }

    forward(be_to_right1, be_to_right1,spd_for_tlf_left,spd_for_tlf_right);//前进
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done2:%d,time:%d\n", recved, (rt_tick_get()));
    }

    for_turnleft(dis_for_tlf_left45, dis_for_tlf_right45,spd_for_left,spd_for_right);//圆弧左转45
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done3:%d,time:%d\n", recved, (rt_tick_get()));
    }

    forward(right1_to_right3, right1_to_right3,0,0);//前进
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done5:%d,time:%d\n", recved, (rt_tick_get()));
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

void to_right_init(void)
{
    tid_to_right = rt_thread_create("tid_to_right",
                                   tid_to_right_entry, RT_NULL,
                                   2048 ,
                                   12 , 10);
    if(tid_to_right != RT_NULL)
        rt_thread_startup(tid_to_right);
}
