#include "tid_chatoN.h"

void tid_chatoN_entry(void *par)
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

    backward(M_to_Q, M_to_Q);

    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }

    back_turnleft(dis_back_tlf_left, dis_back_tlf_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done2:%d,time:%d\n", recved, (rt_tick_get()));
    }

    backward(Q_to_S, Q_to_S);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done3:%d,time:%d\n", recved, (rt_tick_get()));
    }

    back_turnleft(dis_back_tlf_left, dis_back_tlf_right);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done4:%d,time:%d\n", recved, (rt_tick_get()));
    }

    backward(S_to_N, S_to_N);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done5:%d,time:%d\n", recved, (rt_tick_get()));
    }
    stop();

    rt_mutex_release(&mission_mu);
}

void chatoN_init(void)
{
    tid_chatoN = rt_thread_create("tid_chatoN",
                                  tid_chatoN_entry, RT_NULL,
                                  2048 ,
                                  12 , 10);
    if(tid_chatoN != RT_NULL)
        rt_thread_startup(tid_chatoN);
}
