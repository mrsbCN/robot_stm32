#include "speed_control.h"
#define K   0.0013315      //(3.1415*125/8192/36)     //总角度-->距离(mm)系数 pi，轮子直径，一圈信号数，减速比

static rt_thread_t tid_speed_control = RT_NULL;
struct rt_can_msg msg_send;
void speed_control(void *par);
rt_int32_t test_u;
float ADRC_Unit[3][15]=
{
/*TD跟踪微分器   改进最速TD,h0=N*h      扩张状态观测器ESO(w0=4wc)           扰动补偿     			非线性组合(wc)*/
/*  r     h      	N0                 beta_01   beta_02    beta_03     	b0      	beta_0			beta_1      beta_2      alpha1  alpha2  zeta */
 {3000 ,0.005 , 	20,               	100,      	300,      1000,      	60,    		0.005,			400,      	20,     		0.8,   1.5,    0.03},
 {3000 ,0.005 , 	20,               	100,      	300,      1000,      	60,    		0.005,			400,      	20,     		0.8,   1.5,    0.03},
 {3000 ,0.005 , 	20,               	100,      	300,      1000,      	60,    		0.005,			400,      	20,     		0.8,   1.5,    0.03},
};

void speed_control_init(void)
{
	msg_send.id = 0x200;
    msg_send.ide = CAN_ID_STD;
    msg_send.rtr = CAN_RTR_DATA;
    msg_send.len = 0x08;

    msg_send.data[4] =  0;
    msg_send.data[5] = 	0;
    msg_send.data[6] =  0;
    msg_send.data[7] = 	0;
	ADRC_Init(ADRC_SPEED, ADRC_Unit,2);
	ADRC_Init(&ADRC_DEV, &ADRC_Unit[2],1);
    tid_speed_control = rt_thread_create("speed_control", speed_control, RT_NULL, 4096, 19, 20);

    if(RT_NULL != tid_speed_control)
        rt_thread_startup(tid_speed_control);
}

void speed_control(void *par)
{
	rt_uint8_t i;
    rt_int16_t ele[2];
	rt_int32_t real_v[2];
    rt_int32_t tar[2] = {0, 0};
	rt_int32_t error = 0;
	rt_uint8_t done,status = 0;

    while(1)
    {
        for(i = 0; i < 2; i++)
        {
			rt_mb_recv(&s_tar_mb[i], (rt_ubase_t *)&tar[i], RT_WAITING_NO);
        }
		if(RT_EOK == rt_mb_recv(&s_error, (rt_ubase_t *)&error, RT_WAITING_NO))
		{
			ADRC_Control(&ADRC_DEV,0,error);
			if(ADRC_DEV.u >0.1)//限幅
			{
				ADRC_DEV.u = 0.1;
			}
			else if(ADRC_DEV.u <-0.1)
			{
				ADRC_DEV.u = -0.1;
			}
		}
		
		if(RT_EOK == rt_mb_recv(&s_kf_mb[0],(rt_ubase_t *)&real_v[0],RT_WAITING_FOREVER))
		{
			rt_mb_recv(&s_kf_mb[1],(rt_ubase_t *)&real_v[1],RT_WAITING_FOREVER);
			test_u = tar[1];
			ADRC_Control(&ADRC_SPEED[0],tar[0]*(1+ADRC_DEV.u),real_v[0]);
			ADRC_Control(&ADRC_SPEED[1],tar[1]*(1-ADRC_DEV.u),real_v[1]);
			ele[0] = (rt_int16_t)ADRC_SPEED[0].u;
			ele[1] = (rt_int16_t)ADRC_SPEED[1].u;
			done = 1;
		}
		
		if(done)
		{
			msg_send.data[0] =  ele[0] >> 8 ;
			msg_send.data[1] =  ele[0];
			msg_send.data[2] =  ele[1] >> 8 ;
			msg_send.data[3] =  ele[1];
			dev_can1.ops->sendmsg(&dev_can1, &msg_send, CAN_TXMAILBOX_0);
			done = 0;
		}
        rt_thread_delay(1);
    }
}

