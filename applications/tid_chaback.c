#include "tid_chaback.h"

void tid_chaback_entry(void *par)
{
    rt_mutex_take(&mission_mu, RT_WAITING_FOREVER);
    rt_uint32_t recved;

    rt_thread_mdelay(2000);
    for(rt_uint8_t i = 0; i < 2; i++)
    {
        motor_pid[i].f_pid_reset(&motor_pid[i]);
        reset_total_angle(&moto_chassis[i]);
    }
    rt_thread_mdelay(2500);

    forward(N_to_S, N_to_S);

    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }

    for_turnright(dis_for_tri_left, dis_for_tri_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done2:%d,time:%d\n", recved, (rt_tick_get()));
    }

    forward(S_to_R, S_to_R);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done3:%d,time:%d\n", recved, (rt_tick_get()));
    }

    for_turnleft(dis_for_tlf_left, dis_for_tlf_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done4:%d,time:%d\n", recved, (rt_tick_get()));
    }

    forward(halfR_to_be, halfR_to_be);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done5:%d,time:%d\n", recved, (rt_tick_get()));
    }
    stop();
    rt_mutex_release(&mission_mu);
}

void chaback_init(void)
{
    tid_chaback = rt_thread_create("tid_chaback",
                                   tid_chaback_entry, RT_NULL,
                                   2048 ,
                                   12 , 10);
    if(tid_chaback != RT_NULL)
        rt_thread_startup(tid_chaback);
}
