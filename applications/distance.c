#include "distance.h"

void distance(void * par);



void dis_init(void)
{
    tid_dis = rt_thread_create("dis_left",distance,RT_NULL,4096,9,10);
		if(RT_NULL != tid_dis)
			rt_thread_startup(tid_dis);
}

#define ABS(x)	( (x>0) ? (x) : (-x) )
void distance(void * par)
{
		rt_uint8_t i,status;
		rt_int32_t total_angle[2];
		rt_int32_t cur_angle[2];
		rt_int32_t dis_tar[2]={99999999,99999999};
		rt_uint32_t recved;
    while(1)
    {
			if(RT_EOK == rt_event_recv(&event_per,EVENT_PER,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&recved))	//如果收到dist事件则开始计算
			{
				for(i=0;i<2;i++)
				{
					rt_mb_recv(&total_mb[i],(rt_ubase_t*)&cur_angle[i],RT_WAITING_FOREVER);					//一直更新当前角度
				}
			}
			
			if(RT_EOK == rt_event_recv(&event_dist,EVENT_DIST,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&recved))	//如果收到dist事件则开始计算
			{
				for(i=0;i<2;i++)
				{
					rt_mb_recv(&dis_tar_mb[i],(rt_ubase_t*)&dis_tar[i],RT_WAITING_NO);	//更新目标
				}
				status =1;
				
				while(status ==1 )
				{
					if(RT_EOK == rt_event_recv(&event_per,EVENT_PER,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&recved))	
					{
						for(i=0;i<2;i++)
						{
							if(RT_EOK == rt_mb_recv(&total_mb[i],(rt_ubase_t*)&total_angle[i],RT_WAITING_FOREVER))
							{
								if(  ABS(total_angle[i] - cur_angle[i]) *K >= ((rt_uint32_t)dis_tar[i]) )
								{
									rt_event_send(&event_done,(EVENT_DONE_LEFT<<i));
									status =0;
								}
							}
						}
					}
				}
				
			}			
    }
}

