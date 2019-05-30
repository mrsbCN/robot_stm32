#include "tid_B_Ntonurse.h"

void tid_B_Ntonurse_entry(void *par)
{
    rt_mutex_take(&mission_mu, RT_WAITING_FOREVER);
    rt_uint32_t recved;

	rt_thread_mdelay(1000);
    rt_thread_mdelay(10);
    for(rt_uint8_t i = 0; i < 2; i++)
    {
        motor_pid[i].f_pid_reset(&motor_pid[i]);
        reset_total_angle(&moto_chassis[i]);
    }
    rt_thread_mdelay(10);

	backward(N_to_nurse,N_to_nurse);
    if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    {
        rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    }

    rt_mb_send(&s_tar_mb[0], 0);
    rt_mb_send(&s_tar_mb[1], 0);

    rt_mutex_release(&mission_mu);
}

void B_Ntonurse_init(void)
{
    tid_B_Ntonurse = rt_thread_create("tid_B_Ntonurse",
                                   tid_B_Ntonurse_entry, RT_NULL,
                                   2048 ,
                                   12 , 10);
    if(tid_B_Ntonurse != RT_NULL)
        rt_thread_startup(tid_B_Ntonurse);
}
