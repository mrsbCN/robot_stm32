#include "distance.h"
#define Kh 0.05
#define Ka 0.1

void distance(void *par);
void distance_turn(void *par);
void dis_init(void)
{
    tid_dis = rt_thread_create("distance", distance, RT_NULL, 4096, 13, 50);
    if(RT_NULL != tid_dis)
        rt_thread_startup(tid_dis);
	
	tid_dis_turn = rt_thread_create("dist_turn", distance_turn, RT_NULL, 2048, 13, 50);
    if(RT_NULL != tid_dis_turn)
        rt_thread_startup(tid_dis_turn);
}

#define ABS(x)	( (x>0) ? (x) : (-x) )
void distance(void *par)
{
    rt_uint8_t i, status;
    i = 0;
	float tar_dist,now_dist,tar_angle;
    rt_int32_t start_loca[2];
    rt_int32_t now_loca[2];
    rt_int32_t tar_loca[2] = {99999999, 99999999};
	rt_int32_t angle100; //�Ƕ��� 100��
	float delta_loca[2],delta_loca_m[2],del[2];  //�ֱ���x2-x1,y2-y1,x-x1,y-y1,ƽ����
	float H,alpha,E;
    rt_uint32_t recved;
    while(1)
    {
        if(RT_EOK == rt_event_recv(&event_per, EVENT_PER, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
        {
            for(i = 0; i < 2; i++)
            {
                rt_mb_recv(&loc_now_mb[i], (rt_ubase_t *)&start_loca[i], RT_WAITING_FOREVER);					//һֱ���µ�ǰ�Ƕ�
            }
        }

        if(RT_EOK == rt_event_recv(&event_loca, EVENT_DIST_FOR|EVENT_DIST_BACK, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_NO, &recved))	//����յ�dist�¼���ʼ����
        {
            for(i = 0; i < 2; i++)
            {
                rt_mb_recv(&dis_tar_mb[i], (rt_ubase_t *)&tar_loca[i], RT_WAITING_NO);	//����Ŀ��
            }
			
            status = 1;
			delta_loca[0] = (tar_loca[0]-start_loca[0]);	//x2-x1
			delta_loca[1] = (tar_loca[1]-start_loca[1]);	//y2-y1
			tar_angle = atan2f(delta_loca[1],delta_loca[0]);
			arm_power_f32(delta_loca,2,&del[0]);
			arm_sqrt_f32(del[0],&tar_dist); //d=sqrt((y2-y1)^2+(x2-x1)^2)
            while(status == 1 )
            {
                if(RT_EOK == rt_event_recv(&event_per, EVENT_PER, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
                {
					rt_mb_recv(&loc_now_mb[0], (rt_ubase_t *)&now_loca[0], RT_WAITING_FOREVER);
					rt_mb_recv(&loc_now_mb[1], (rt_ubase_t *)&now_loca[1], RT_WAITING_FOREVER);
					rt_mb_recv(&angle_to_use,(rt_ubase_t *)&angle100,RT_WAITING_FOREVER);
					if(recved == EVENT_DIST_FOR)//ǰ��ʱ����ʼ��ͷ��90��
					{
						angle100 +=900;
					}
					else
					{
						angle100 -=900;
					}
					delta_loca_m[0] = (now_loca[0]-start_loca[0]);		//x-x1
					delta_loca_m[1] = (now_loca[1]-start_loca[1]);		//y-y1
					arm_power_f32(delta_loca_m,2,&del[1]);
					arm_sqrt_f32(del[1],&now_dist);
					if(now_dist >= tar_dist)
					{
						rt_event_send(&event_done,EVENT_DONE);
						status = 0;
						break;
					}
					H = ((delta_loca[1])*(delta_loca_m[0])-(delta_loca[0])*(delta_loca_m[1]))/tar_dist;
					alpha = tar_angle/PI*180.0 - angle100/100.0; //ת�ɽǶ�
					E = Kh*H+Ka*alpha;
					if(recved == EVENT_DIST_BACK)
					{E = -E;}
                }
            }

        }
    }
}

void distance_turn(void *par)
{
	rt_uint8_t status=0;
	rt_int32_t now_loca[2];
	rt_int32_t start_angle;
	rt_int32_t now_angle;
	rt_int32_t tar_angle = 0;
	while(1)
    {
		if(RT_EOK == rt_event_recv(&event_loca, EVENT_DIST_TURN, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, RT_NULL))	//����յ�dist�¼���ʼ����
        {
			rt_mb_recv(&angle_to_use,(rt_ubase_t *)&start_angle,RT_WAITING_FOREVER);
            rt_mb_recv(&dis_tar_mb[0], (rt_ubase_t *)&tar_angle, RT_WAITING_NO);	//����xĿ�����䴫����ת�Ƕ�

			rt_mb_recv(&loc_now_mb[0], (rt_ubase_t *)&now_loca[0], RT_WAITING_FOREVER);
			rt_mb_recv(&loc_now_mb[1], (rt_ubase_t *)&now_loca[1], RT_WAITING_FOREVER);  //ֻ��Ϊ���������
			rt_mb_recv(&angle_to_use,(rt_ubase_t *)&now_angle,RT_WAITING_FOREVER);
			status = 1;
			while(status == 1 )
            {
				if(abs(now_angle-start_angle) >= tar_angle)  //���ﲻ+-90�ȣ�ֱ�ӱȲ�ֵ
				{
					rt_event_send(&event_done,EVENT_DONE);
					status = 0;
					break;
				}
			}
		}
	}
}
