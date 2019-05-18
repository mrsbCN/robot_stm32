#include "calculator.h"



void cal(void * par);

moto_measure_t moto_chassis[2] = {0};

struct rt_can_msg msg_send; 

void get_total_angle(moto_measure_t *p);
void get_moto_offset(moto_measure_t *ptr, rt_uint8_t* hcan);
void get_moto_measure(moto_measure_t *ptr, rt_uint8_t* hcan);

void cal_init(void)
{
	
		
		msg_send.id = 0x200;
		msg_send.ide = CAN_ID_STD;
		msg_send.rtr = CAN_RTR_DATA;
		msg_send.len = 0x08; 
		
		msg_send.data[4] =  0;
		msg_send.data[5] = 	0;
		msg_send.data[6] =  0;
		msg_send.data[7] = 	0;
		tid_cal = rt_thread_create("cal",cal,RT_NULL,4096,20,10);			
		
		if(RT_NULL != tid_cal)
			rt_thread_startup(tid_cal);

}

void cal(void * par)
{
		rt_uint8_t i;
		rt_uint8_t recv[3][8]={0};
		rt_int16_t ele[2];
		rt_int32_t tar[2];
		PID_TypeDef motor_pid[2];
	
		
		do
		{
				for(i=0;i<2;i++)
				{
					rt_ringbuffer_get(&s_cur_rb[i],recv[i],8);
				}
		}while((recv[0][7] !=0) || (recv[1][7] !=0));
		
		for(i=0;i<2;i++)
		{
		rt_ringbuffer_get(&s_cur_rb[i],recv[i],8);
		}
		
		for(i=0;i<2;i++)
		{
		rt_ringbuffer_get(&s_cur_rb[i],recv[i],8);
		get_moto_offset(&moto_chassis[i],recv[i]);
		}
		rt_thread_mdelay(5);
		 for(int i=0; i<2; i++)
    {	
			pid_init(&motor_pid[i]);
			motor_pid[i].f_param_init(&motor_pid[i],	//PID_TypeDef * pid
																PID_Speed,			//PID_ID   id
																10000,					//rt_uint16_t maxout
																5000,						//rt_uint16_t intergral_limit
																10,							//float deadband
																0,							//rt_uint16_t period
																4000,						//rt_int16_t  max_err
																0,							//rt_int16_t  target
																1.5,						//float 	kp
																0.1,						//float 	ki
																0.4);						  //float 	kd
    }
	
		
    while(1)
    {
				for(i=0;i<2;i++)
				{
					if(RT_EOK == rt_mb_recv(&s_tar_mb[i],(rt_ubase_t*)&tar[i],RT_WAITING_NO))
					{
						motor_pid[i].target = tar[i];
					}
				}
				
				for(i=0;i<2;i++)
				{
					if( 8 ==rt_ringbuffer_get(&s_cur_rb[i],recv[i],8))
					{
							get_moto_measure(&moto_chassis[i],recv[i]);
							motor_pid[i].f_cal_pid(&motor_pid[i],moto_chassis[i].speed_rpm);
							ele[i] = motor_pid[i].output;
							rt_mb_send(&total_mb[i],moto_chassis[i].total_angle);
					}
				}
				rt_event_send(&event_dist,EVENT_FLAG1);
				
				msg_send.data[0] =  ele[0] >>8 ;
				msg_send.data[1] =  ele[0];
				msg_send.data[2] =  ele[1] >>8 ;
				msg_send.data[3] =  ele[1];
				dev_can1.ops->sendmsg(&dev_can1,&msg_send,CAN_TXMAILBOX_0);
				//LOG_I("s:%d,%d;l:%d,%d,%d,%d,%d,%d;r:%d,%d,%d,%d,%d,%d.", 
				//ele[0],ele[1],recv[0][0],recv[0][1],recv[0][2],recv[0][3],recv[0][4],recv[0][5],
				//recv[1][0],recv[1][1],recv[1][2],recv[1][3],recv[1][4],recv[1][5]);

				for(i = 0;i<4;i++)
				{
					recv[3][i] = msg_send.data[i];
				}
				rt_mq_send(&sdcard_mq,recv,20);
				rt_thread_mdelay(3);		
    }
}



void get_moto_measure(moto_measure_t *ptr, rt_uint8_t* hcan)
{

	ptr->last_angle = ptr->angle;
	ptr->angle = (uint16_t)(hcan[0]<<8 | hcan[1]) ;
	ptr->speed_rpm  = (int16_t)(hcan[2]<<8 | hcan[3]);
	ptr->real_current = (hcan[4]<<8 | hcan[5])*5.f/16384.f;

	ptr->hall = hcan[6];
	
	
	if(ptr->angle - ptr->last_angle > 4096)
		ptr->round_cnt --;
	else if (ptr->angle - ptr->last_angle < -4096)
		ptr->round_cnt ++;
	ptr->total_angle = ptr->round_cnt * 8192 + ptr->angle - ptr->offset_angle;
}

/*this function should be called after system+can init */
void get_moto_offset(moto_measure_t *ptr, rt_uint8_t* hcan)     //加入重置所有参数
{
	ptr->angle = (uint16_t)(hcan[0]<<8 | hcan[1]) ;
	ptr->offset_angle = ptr->angle;
}


#define ABS(x)	( (x>0) ? (x) : (-x) )
/**
*@bref 电机上电角度=0， 之后用这个函数更新3510电机的相对开机后（为0）的相对角度。
	*/
void get_total_angle(moto_measure_t *p){
	
	int res1, res2, delta;
	if(p->angle < p->last_angle){			//可能的情况
		res1 = p->angle + 8192 - p->last_angle;	//正转，delta=+
		res2 = p->angle - p->last_angle;				//反转	delta=-
	}else{	//angle > last
		res1 = p->angle - 8192 - p->last_angle ;//反转	delta -
		res2 = p->angle - p->last_angle;				//正转	delta +
	}
	//不管正反转，肯定是转的角度小的那个是真的
	if(ABS(res1)<ABS(res2))
		delta = res1;
	else
		delta = res2;

	p->total_angle += delta;
	p->last_angle = p->angle;
}
