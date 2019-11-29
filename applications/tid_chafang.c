#include "tid_chafang.h"

void tid_chafang_entry(void *par)
{
    rt_mutex_take(&mission_mu, RT_WAITING_FOREVER);
    rt_uint32_t recved;	
	stop_to_for();
	rt_thread_mdelay(20);
	
	rt_event_send(&event_pwm,EVENT_PWM_CAM);
	rt_pin_write(POWERCI_PIN, PIN_LOW);
	forward(loc_R_x,loc_R_y,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }

	turnleft(90,90,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_for();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	forward(loc_Q_x,loc_Q_y,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	turnright(0,0,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_for();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	forward(loc_M_x,loc_M_y-300,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_back();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }

	wait_for_patient();//一直在按键事件中等待，或10s

	backward(loc_Q_x,loc_Q_y+40,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }

	turnleft(90,90,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_back();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	backward(loc_S_x,loc_S_y+40,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	turnright(0,0,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_for();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	forward(loc_N_x,loc_N_y-300,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_back();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	wait_for_patient();//一直在按键事件中等待，或10s
	
	backward(loc_S_x,loc_S_y,0,0);
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
	
	backward(loc_R_x+250,loc_R_y,0,0);
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
	
	backward(loc_half_be_x,loc_half_be_y,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_for();
		rt_thread_mdelay(50);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
    rt_mutex_release(&mission_mu);
}

void chafang_init(void)
{
    tid_chafang = rt_thread_create("tid_chafang",
                                   tid_chafang_entry, RT_NULL,
                                   2048 ,
                                   12 , 10);
    if(tid_chafang != RT_NULL)
        rt_thread_startup(tid_chafang);
}
