#include "tid_to_B.h"

void tid_to_B_entry(void *par)
{
    rt_mutex_take(&mission_mu, RT_WAITING_FOREVER);
    rt_uint32_t recved;	
	stop_to_back();
	rt_thread_mdelay(20);

	forward(loc_R_x+250,loc_R_y,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	turnright(-90,-90,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_for();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	forward(loc_S_x+250,loc_S_y,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	turnright(-180,-180,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_for();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }

	forward(loc_nurse_x+250,loc_nurse_y,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_back();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	rt_event_send(&event_pwm,EVENT_PWM_LEFT);
	rt_thread_mdelay(6000);
//取药步骤
	
	backward(loc_S_x+250,loc_S_y,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	turnleft(-90,-90,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	turnleft(0,0,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_for();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	forward(loc_N_x+250,loc_N_y-50,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_back();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	rt_event_send(&event_pwm,EVENT_PWM_RIGHT);
	rt_thread_mdelay(3000);
//放药步骤
	
	backward(loc_S_x+250,loc_S_y,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }

	turnright(-90,-90,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_for();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	turnright(-180,-180,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_for();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	forward(loc_nurse2_x+300,loc_nurse2_y,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_back();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	rt_event_send(&event_pwm,EVENT_PWM_LEFT);
	rt_thread_mdelay(6000);
//加入取药

	backward(loc_S_x+300,loc_S_y,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	turnleft(-90,-90,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_back();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	backward(loc_Q_x+300,loc_Q_y,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	turnleft(0,0,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_for();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	forward(loc_M_x+250,loc_M_y-100,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_back();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	rt_event_send(&event_pwm,EVENT_PWM_RIGHT);	
	rt_thread_mdelay(3000);
//加入放药
	
	backward(loc_Q_x+300,loc_Q_y,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	turnright(-90,-90,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_for();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	forward(loc_R_x+300,loc_R_y-100,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	turnright(-180,-180,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_for();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	forward(loc_begin_x+300,loc_begin_y-400,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }

	rt_pwm_set(pwm_dev_top, PWM_TOP, period, 3000000);
    rt_mutex_release(&mission_mu);
}

void to_B_init(void)
{
    tid_to_B = rt_thread_create("tid_to_B",
                                   tid_to_B_entry, RT_NULL,
                                   2048 ,
                                   12 , 10);
    if(tid_to_B != RT_NULL)
        rt_thread_startup(tid_to_B);
}
