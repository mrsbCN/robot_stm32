#include "tid_tonurse.h"

void tid_tonurse_entry(void *par)
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

    rt_mb_send(&s_tar_mb[0], spd_back_left);
    rt_mb_send(&s_tar_mb[1], spd_back_right);
    rt_mb_send(&dis_tar_mb[0], M_to_Q);
    rt_mb_send(&dis_tar_mb[1], M_to_Q);
    rt_event_send(&event_dist, EVENT_DIST);


    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }

    rt_mb_send(&s_tar_mb[0], spd_back_tlf_left);
    rt_mb_send(&s_tar_mb[1], spd_back_tlf_right);
    rt_mb_send(&dis_tar_mb[0], dis_back_tlf_left);
    rt_mb_send(&dis_tar_mb[1], dis_back_tlf_right);
    rt_event_send(&event_dist, EVENT_DIST);

    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done2:%d,time:%d\n", recved, (rt_tick_get()));
    }

    rt_mb_send(&s_tar_mb[0], spd_back_left);
    rt_mb_send(&s_tar_mb[1], spd_back_right);
    rt_mb_send(&dis_tar_mb[0], Q_to_S);
    rt_mb_send(&dis_tar_mb[1], Q_to_S);
    rt_event_send(&event_dist, EVENT_DIST);


    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done3:%d,time:%d\n", recved, (rt_tick_get()));
    }

    rt_mb_send(&s_tar_mb[0], spd_back_tlf_left);
    rt_mb_send(&s_tar_mb[1], spd_back_tlf_right);
    rt_mb_send(&dis_tar_mb[0], dis_back_tlf_left);
    rt_mb_send(&dis_tar_mb[1], dis_back_tlf_right);
    rt_event_send(&event_dist, EVENT_DIST);

    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done4:%d,time:%d\n", recved, (rt_tick_get()));
    }

    rt_mb_send(&s_tar_mb[0], spd_back_left);
    rt_mb_send(&s_tar_mb[1], spd_back_right);
    rt_mb_send(&dis_tar_mb[0], S_to_N);
    rt_mb_send(&dis_tar_mb[1], S_to_N);
    rt_event_send(&event_dist, EVENT_DIST);

    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done5:%d,time:%d\n", recved, (rt_tick_get()));
    }
    rt_mb_send(&s_tar_mb[0], 0);
    rt_mb_send(&s_tar_mb[1], 0);

    rt_mutex_release(&mission_mu);
}

void tonurse_init(void)
{
    tid_tonurse = rt_thread_create("tid_tonurse",
                                   tid_tonurse_entry, RT_NULL,
                                   2048 ,
                                   12 , 10);
    if(tid_tonurse != RT_NULL)
        rt_thread_startup(tid_tonurse);
}
