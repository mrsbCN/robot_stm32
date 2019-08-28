#include "tid_left_to_right.h"

void tid_left_to_right_entry(void *par)
{
    rt_mutex_take(&mission_mu, RT_WAITING_FOREVER);
    rt_uint32_t recved;

	rt_thread_mdelay(10);	
	turnleft(20,20,0,0);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_back();
		rt_thread_mdelay(200);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_cir_left2_x,loc_cir_left2_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_cir_left3_x,loc_cir_left3_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_cir_left4_x,loc_cir_left4_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_cir_left5_x,loc_cir_left5_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_cir_left6_x,loc_cir_left6_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_cir_left7_x,loc_cir_left7_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	rt_pin_write(OPENMV_PIN,PIN_LOW);
	
	backward(loc_cir_right7_x,loc_cir_right7_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_cir_right6_x,loc_cir_right6_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_cir_right5_x,loc_cir_right5_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_cir_right4_x,loc_cir_right4_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_cir_right3_x,loc_cir_right3_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_cir_right2_x,loc_cir_right2_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_right_done_x+100,loc_right_done_y-70,0,0);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
    stop();
	rt_thread_mdelay(20);
	turnleft(180,180,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
    stop_to_for();
	rt_event_send(&event_pwm,EVENT_PWM_RIGHT);
	wait_for_patient();
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
