#include "tid_chatoM.h"

void tid_chatoM_entry(void *par)
{
		rt_mutex_take(&mission_mu,RT_WAITING_FOREVER);
		rt_uint32_t recved;
		
		rt_mb_send(&s_tar_mb[0],spd_for_left);
		rt_mb_send(&s_tar_mb[1],spd_for_right);
    rt_mb_send(&dis_tar_mb[0],be_to_R);
		rt_mb_send(&dis_tar_mb[1],be_to_R);
		rt_event_send(&event_dist,EVENT_DIST);

	
		if (RT_EOK == rt_event_recv(&event_done,EVENT_DONE_LEFT|EVENT_DONE_RIGHT,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&recved))
		{
			rt_kprintf("done1:%d,time:%d\n",recved,(rt_tick_get()));
		}
		
		rt_mb_send(&s_tar_mb[0],spd_for_tlf_left);
		rt_mb_send(&s_tar_mb[1],spd_for_tlf_right);	
		rt_mb_send(&dis_tar_mb[0],dis_for_tlf_left);
		rt_mb_send(&dis_tar_mb[1],dis_for_tlf_right);
		rt_event_send(&event_dist,EVENT_DIST);

		if (RT_EOK == rt_event_recv(&event_done,EVENT_DONE_LEFT|EVENT_DONE_RIGHT,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&recved))
		{
			rt_kprintf("done2:%d,time:%d\n",recved,(rt_tick_get()));
		}
		
		rt_mb_send(&s_tar_mb[0],spd_for_left);
		rt_mb_send(&s_tar_mb[1],spd_for_right);
    rt_mb_send(&dis_tar_mb[0],R_to_Q);
		rt_mb_send(&dis_tar_mb[1],R_to_Q);
		rt_event_send(&event_dist,EVENT_DIST);

		
		if (RT_EOK == rt_event_recv(&event_done,EVENT_DONE_LEFT|EVENT_DONE_RIGHT,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&recved))
		{
			rt_kprintf("done3:%d,time:%d\n",recved,(rt_tick_get()));
		}
		
		rt_mb_send(&s_tar_mb[0],spd_for_tri_left);
		rt_mb_send(&s_tar_mb[1],spd_for_tri_right);	
		rt_mb_send(&dis_tar_mb[0],dis_for_tri_left);
		rt_mb_send(&dis_tar_mb[1],dis_for_tri_right);
		rt_event_send(&event_dist,EVENT_DIST);
		
		if (RT_EOK == rt_event_recv(&event_done,EVENT_DONE_LEFT|EVENT_DONE_RIGHT,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&recved))
		{
			rt_kprintf("done4:%d,time:%d\n",recved,(rt_tick_get()));
		}
		
		rt_mb_send(&s_tar_mb[0],spd_for_left);
		rt_mb_send(&s_tar_mb[1],spd_for_right);
    rt_mb_send(&dis_tar_mb[0],Q_to_M);
		rt_mb_send(&dis_tar_mb[1],Q_to_M);
		rt_event_send(&event_dist,EVENT_DIST);
		
		if (RT_EOK == rt_event_recv(&event_done,EVENT_DONE_LEFT|EVENT_DONE_RIGHT,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&recved))
		{
			rt_kprintf("done5:%d,time:%d\n",recved,(rt_tick_get()));
		}
		
		rt_mb_send(&s_tar_mb[0],0);
		rt_mb_send(&s_tar_mb[1],0);
		rt_mutex_release(&mission_mu);
}

void chatoM_init(void)
{
		tid_chatoM = rt_thread_create("tid_chatoM",
									tid_chatoM_entry, RT_NULL,
									2048 ,
									12 , 10);
		if(tid_chatoM != RT_NULL)
			rt_thread_startup(tid_chatoM);
}
