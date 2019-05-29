#include "tid_A_toM.h"

void tid_A_toM_entry(void *par)
{
    rt_mutex_take(&mission_mu, RT_WAITING_FOREVER);
    rt_uint32_t recved;

    rt_thread_mdelay(10);
    for(rt_uint8_t i = 0; i < 2; i++)
    {
        motor_pid[i].f_pid_reset(&motor_pid[i]);
        reset_total_angle(&moto_chassis[i]);
    }
    rt_thread_mdelay(10);

	forward(nurse_to_S,nurse_to_S);

    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }

	for_turnleft(dis_for_tlf_left,dis_for_tlf_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done2:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	forward(S_to_Q,S_to_Q);

    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done3:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	for_turnright(dis_for_tri_left,dis_for_tri_right);

    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done4:%d,time:%d\n", recved, (rt_tick_get()));
    }
	
	forward(Q_to_M,Q_to_M);

    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done5:%d,time:%d\n", recved, (rt_tick_get()));
    }
    rt_mb_send(&s_tar_mb[0], 0);
    rt_mb_send(&s_tar_mb[1], 0);

    rt_mutex_release(&mission_mu);
}

void A_toM_init(void)
{
    tid_A_toM = rt_thread_create("tid_A_toM",
                                   tid_A_toM_entry, RT_NULL,
                                   2048 ,
                                   12 , 10);
    if(tid_A_toM != RT_NULL)
        rt_thread_startup(tid_A_toM);
}
