#include "tid_to_A.h"

void tid_to_A_entry(void *par)
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
		stop_to_back();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	backward(loc_Q_x+120,loc_Q_y,0,0);
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
	
	forward(loc_M_x+120,loc_M_y-50,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_back();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	rt_event_send(&event_pwm,EVENT_PWM_RIGHT);
	rt_thread_mdelay(3000);	
//加入放药
	

	backward(loc_Q_x+250,loc_Q_y,0,0);
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
	
	forward(loc_nurse2_x+280,loc_nurse2_y,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_back();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	rt_event_send(&event_pwm,EVENT_PWM_LEFT);
	rt_thread_mdelay(6000);
//加入取药


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
	
	forward(loc_N_x+250,loc_N_y-100,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_back();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	rt_event_send(&event_pwm,EVENT_PWM_RIGHT);
	rt_thread_mdelay(3000);
//加入放药

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
		stop_to_back();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	backward(loc_R_x+250,loc_R_y-100,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	turnleft(0,0,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_back();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	backward(loc_begin_x+250,loc_begin_y-500,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	rt_pwm_set(pwm_dev_top, PWM_TOP, period, 3000000);
    rt_mutex_release(&mission_mu);
}

void to_A_init(void)
{
    tid_to_A = rt_thread_create("tid_to_A",
                                   tid_to_A_entry, RT_NULL,
                                   2048 ,
                                   12 , 10);
    if(tid_to_A != RT_NULL)
        rt_thread_startup(tid_to_A);
}
