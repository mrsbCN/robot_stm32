#include "tid_right_to_left.h"

void tid_right_to_left_entry(void *par)
{
    rt_mutex_take(&mission_mu, RT_WAITING_FOREVER);
    rt_uint32_t recved;

	rt_thread_mdelay(10);
	turnright(-20,-20,0,0);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
		stop_to_back();
		rt_thread_mdelay(200);
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_cir_right2_x+120,loc_cir_right2_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_cir_right3_x+120,loc_cir_right3_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_cir_right4_x+120,loc_cir_right4_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_cir_right5_x+120,loc_cir_right5_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_cir_right6_x+120,loc_cir_right6_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_cir_right7_x+120,loc_cir_right7_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	rt_pin_write(OPENMV_PIN,PIN_LOW);
	
	backward(loc_cir_left7_x+120,loc_cir_left7_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_cir_left6_x+120,loc_cir_left6_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_cir_left5_x+120,loc_cir_left5_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_cir_left4_x+120,loc_cir_left4_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_cir_left3_x+120,loc_cir_left3_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_cir_left2_x+120,loc_cir_left2_y,spd_back_left,spd_back_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
	backward(loc_left_done_x+120,loc_left_done_y-60,0,0);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
    stop();
	rt_thread_mdelay(20);
	turnright(-180,-180,0,0);
	if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }
    stop_to_for();
	rt_event_send(&event_pwm,EVENT_PWM_LEFT);
	wait_for_patient();
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
