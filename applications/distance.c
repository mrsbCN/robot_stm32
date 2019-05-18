#include "distance.h"

void distance(void * par);



void dis_init(rt_uint32_t l)
{
    tid_dis = rt_thread_create("dis_left",distance,(void*)l,4096,9,10);
		
		if(RT_NULL != tid_dis)
			rt_thread_startup(tid_dis);
}

void dis_kill(void)
{
	rt_thread_detach(tid_dis);
}
void distance(void * par)
{
		
		rt_uint8_t i;
		rt_int32_t total0[2];
		rt_int32_t total_angle[2];
		rt_uint32_t recved;
		for(i=0;i<2;i++)
		{
			rt_mb_recv(&total_mb[i],(rt_ubase_t*)&total0[i],RT_WAITING_FOREVER);
		}
    while(1)
    {
			if (RT_EOK == rt_event_recv(&event_dist,EVENT_FLAG1,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&recved))
			{
				for(i=0;i<2;i++)
				{
					if(RT_EOK == rt_mb_recv(&total_mb[i],(rt_ubase_t*)&total_angle[i],RT_WAITING_FOREVER))
					{
						if(  ABS(total_angle[i] - total0[i]) *K >= ((rt_uint32_t)par) )
						{
							rt_event_send(&event_done,(EVENT_DONE_LEFT<<i));
						}
					}
				}
			}
    }
}

