#include "distance.h"

void distance(void *par);

void dis_init(void)
{
    tid_dis = rt_thread_create("distance", distance, RT_NULL, 4096, 13, 50);
    if(RT_NULL != tid_dis)
        rt_thread_startup(tid_dis);
}

#define ABS(x)	( (x>0) ? (x) : (-x) )
void distance(void *par)
{
    rt_uint8_t i, status;
    i = 0;
    rt_int32_t total_angle[2];
    rt_int32_t cur_angle[2];
    rt_int32_t now[2];
    rt_int32_t dis_tar[2] = {99999999, 99999999};
    rt_uint32_t recved;
    while(1)
    {
        if(RT_EOK == rt_event_recv(&event_per, EVENT_PER, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
        {
            for(i = 0; i < 2; i++)
            {
                rt_mb_recv(&total_mb[i], (rt_ubase_t *)&cur_angle[i], RT_WAITING_FOREVER);					//一直更新当前角度
            }
        }

        if(RT_EOK == rt_event_recv(&event_dist, EVENT_DIST, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_NO, &recved))	//如果收到dist事件则开始计算
        {
            for(i = 0; i < 2; i++)
            {
                rt_mb_recv(&dis_tar_mb[i], (rt_ubase_t *)&dis_tar[i], RT_WAITING_FOREVER);	//更新目标
            }
            status = 1;

            if(RT_EOK == rt_event_recv(&event_per, EVENT_PER, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
            {
                for(i = 0; i < 2; i++)
                {
                    rt_mb_recv(&total_mb[i], (rt_ubase_t *)&cur_angle[i], RT_WAITING_FOREVER);					//更新当前角度
                }
            }

            while(status == 1 )
            {
                if(RT_EOK == rt_event_recv(&event_per, EVENT_PER, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
                {
                    for(i = 0; i < 2; i++)
                    {
                        if(RT_EOK == rt_mb_recv(&total_mb[i], (rt_ubase_t *)&total_angle[i], RT_WAITING_FOREVER))
                        {
                            now[i] = labs(total_angle[i] - cur_angle[i]) * K;
                            if(  now[i] >= (dis_tar[i]) )
                            {
                                rt_event_send(&event_done, (EVENT_DONE_LEFT << i));
                                status = 0;
                                rt_kprintf("dis time:%d\n", (rt_tick_get()));
                                rt_kprintf("angle:%d,%d,%d,%d\n\n", total_angle[i], cur_angle[i], dis_tar[i], i);
                                break;
                            }
                        }
                    }
                    //rt_kprintf("total_angle[0]:%d \t cur_angle:%d \t now:%d \n",total_angle[0],cur_angle[0],now[0]);
                }
            }

        }
    }
}

