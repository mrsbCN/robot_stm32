#include "tid_toR.h"

void tid_toR_entry(void *par)
{
		rt_uint32_t recved;
		
    rt_mb_send(&dis_tar_mb[0],be_to_R);
		rt_mb_send(&dis_tar_mb[1],be_to_R);
		rt_event_send(&event_dist,EVENT_DIST);
	
		rt_mb_send(&s_tar_mb[0],spd_for_left);
		rt_mb_send(&s_tar_mb[1],spd_for_right);
	
		if (RT_EOK == rt_event_recv(&event_done,EVENT_DONE_LEFT|EVENT_DONE_RIGHT,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&recved))
		{
			rt_kprintf("done1:%d,time:%d\n",recved,(rt_tick_get()));
		}
		
		rt_mb_send(&dis_tar_mb[0],turnleft_left);
		rt_mb_send(&dis_tar_mb[1],turnleft_right);
		rt_event_send(&event_dist,EVENT_DIST);
		rt_mb_send(&s_tar_mb[0],spd_for_tlf_left);
		rt_mb_send(&s_tar_mb[1],spd_for_tlf_right);	
		if (RT_EOK == rt_event_recv(&event_done,EVENT_DONE_LEFT|EVENT_DONE_RIGHT,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&recved))
		{
			rt_kprintf("done2:%d,time:%d\n",recved,(rt_tick_get()));
		}
			
    rt_mb_send(&dis_tar_mb[0],R_to_Q);
		rt_mb_send(&dis_tar_mb[1],R_to_Q);
		rt_event_send(&event_dist,EVENT_DIST);
		rt_mb_send(&s_tar_mb[0],spd_for_left);
		rt_mb_send(&s_tar_mb[1],spd_for_right);
		
		if (RT_EOK == rt_event_recv(&event_done,EVENT_DONE_LEFT|EVENT_DONE_RIGHT,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&recved))
		{
			rt_kprintf("done3:%d,time:%d\n",recved,(rt_tick_get()));
		}
		
		rt_mb_send(&s_tar_mb[0],0);
		rt_mb_send(&s_tar_mb[1],0);
}

void toR_init(void)
{
		tid_toR = rt_thread_create("tid_toR",
									tid_toR_entry, RT_NULL,
									2048 ,
									9 , 10);
		if(tid_toR != RT_NULL)
			rt_thread_startup(tid_toR);
}
