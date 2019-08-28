#include "calculator.h"

void cal(void *par);

moto_measure_t moto_chassis[2] = {0};
static rt_thread_t tid_cal = RT_NULL;
kalman spd_filter[2];
kalman angle_filter;
rt_int32_t test_x,test_y,test_zeta;

void get_total_angle(moto_measure_t *p);
void get_moto_offset(moto_measure_t *ptr, rt_uint8_t *hcan);
void get_moto_measure(moto_measure_t *ptr, rt_uint8_t *hcan);


void cal_init(void)
{

	kalmanCreate(&spd_filter[0],10,500);
	kalmanCreate(&spd_filter[1],10,500);
	kalmanCreate(&angle_filter,10,20);	
    tid_cal = rt_thread_create("cal", cal, RT_NULL, 4096, 18, 20);

    if(RT_NULL != tid_cal)
        rt_thread_startup(tid_cal);

}

void cal(void *par)
{
	rt_uint32_t recved;
    rt_uint8_t i;
    rt_uint8_t recv[3][8] = {0};
	rt_uint8_t done[2]={0, 0};
	char uart_rx[44];
	float x,y,dr=0;
	x = loc_begin_x;
	y = loc_begin_y;
	float omg,last_zeta,zeta=0.0;
    do
    {
        for(i = 0; i < 2; i++)
        {
            rt_ringbuffer_get(&s_cur_rb[i], recv[i], 8);
        }
    }
    while((recv[0][7] != 0) || (recv[1][7] != 0));

	rt_thread_mdelay(10);
	while(moto_chassis[0].offset_angle == 0 && moto_chassis[0].offset_angle ==0)
	{
		for(i = 0; i < 2; i++)
		{
			rt_ringbuffer_get(&s_cur_rb[i], recv[i], 8);
			get_moto_offset(&moto_chassis[i], recv[i]);
		}
		rt_thread_mdelay(10);
	}

	for(i = 0; i < 2; i++)
	{
		if( 8 == rt_ringbuffer_get(&s_cur_rb[i], recv[i], 8))
		{
			get_moto_measure(&moto_chassis[i], recv[i]);
		}
	}
	
    while(1)
    {
		rt_event_recv(&event_dir, EVENT_FOR|EVENT_BACK|EVENT_TURN, RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR, RT_WAITING_NO, &recved);

		if(RT_EOK == rt_mq_recv(&rx_mq,uart_rx,44,RT_WAITING_NO))
		{
			
			for(i=0;i<34;i++)
			{
				if(uart_rx[i] == 0x55 && uart_rx[i+1] == 0x53)
				{
					zeta= (short)((uart_rx[i+7]<<8|uart_rx[i+6]))/32768.0*PI;
					//for(rt_uint8_t j=i+11;j<34;j++)//暂时不用omg
					//{
					//	if(uart_rx[i] == 0x55 && uart_rx[i+1] == 0x53)
					//	{
					//		omg = (short)((uart_rx[j+7]<<8|uart_rx[j+6]))/32768.0*2000/180.0*PI;
					//		break;
					//	}
					//}
					break;
				}
				//lse if(uart_rx[i] == 0x55 && uart_rx[i+1] == 0x52)
				//
				//	omg= (short)((uart_rx[i+7]<<8|uart_rx[i+6]))/32768.0*2000/180.0*PI;
				//	for(rt_uint8_t j=i+11;j<34;j++)
				//	{
				//		if(uart_rx[i] == 0x55 && uart_rx[i+1] == 0x52)
				//		{
				//			zeta = (short)((uart_rx[j+7]<<8|uart_rx[j+6]))/32768.0*PI;
				//			break;
				//		}
				//	}
				//	break;
				//
			}
			if(recved == EVENT_FOR)
			{
				zeta +=PI/2;
			}
			else if(recved == EVENT_BACK)
			{
				zeta -=PI/2;
			}
		}
		
        for(i = 0; i < 2; i++)
        {
            if( 8 == rt_ringbuffer_get(&s_cur_rb[i], recv[i], 8))
            {
                get_moto_measure(&moto_chassis[i], recv[i]);
				moto_chassis[i].speed_rpm = KalmanFilter(&spd_filter[i],moto_chassis[i].speed_rpm); 
				done[i] = 1;
            }
        }
		if(done[0] && done[1])
		{
			dr = abs(moto_chassis[0].delta_angle-moto_chassis[1].delta_angle)/2 * K; //因为两轮相反安装，所以加-
			x += dr*arm_cos_f32(zeta);
			y += dr*arm_sin_f32(zeta);
			rt_mb_send(&loc_now_mb[0],(rt_int32_t)x);
			rt_mb_send(&loc_now_mb[1],(rt_int32_t)y);
			rt_mb_send(&angle_to_use,(rt_int32_t)(zeta*6000));
			rt_mb_send(&s_kf_mb[0],moto_chassis[0].speed_rpm );
			rt_mb_send(&s_kf_mb[1],moto_chassis[1].speed_rpm );		//发送滤波后的速度
			rt_event_send(&event_per, EVENT_PER);
			
		}
		test_x = x;
		test_y = y;
		test_zeta =zeta*5730;
        rt_thread_delay(1);
    }
}



void get_moto_measure(moto_measure_t *ptr, rt_uint8_t *hcan)
{

    ptr->last_angle = ptr->angle;
    ptr->angle = (uint16_t)(hcan[0] << 8 | hcan[1]) ;
    ptr->speed_rpm  = (int16_t)(hcan[2] << 8 | hcan[3]);
    ptr->real_current = (hcan[4] << 8 | hcan[5]) * 5.f / 16384.f;

    ptr->hall = hcan[6];
	ptr->delta_angle = ptr->angle - ptr->last_angle;
    if(ptr->delta_angle > 4096)
	{
		ptr->round_cnt --;
		ptr->delta_angle -= 8192;
	}
    else if (ptr->delta_angle < -4096)
	{
        ptr->round_cnt ++;
		ptr->delta_angle += 8192;
	}
    ptr->total_angle = ptr->round_cnt * 8192 + ptr->angle - ptr->offset_angle;
}

/*this function should be called after system+can init */
void get_moto_offset(moto_measure_t *ptr, rt_uint8_t *hcan)     //加入重置所有参数
{

    ptr->angle = (uint16_t)(hcan[0] << 8 | hcan[1]) ;
    ptr->offset_angle = ptr->angle;
}


void reset_total_angle(moto_measure_t *ptr)
{
    ptr->round_cnt = 0;
    ptr->offset_angle = ptr->angle;
    ptr->total_angle = 0;
}


#define ABS(x)	( (x>0) ? (x) : (-x) )
/**
*@bref 电机上电角度=0， 之后用这个函数更新3510电机的相对开机后（为0）的相对角度。
	*/
void get_total_angle(moto_measure_t *p)
{

    int res1, res2, delta;
    if(p->angle < p->last_angle) 			//可能的情况
    {
        res1 = p->angle + 8192 - p->last_angle;	//正转，delta=+
        res2 = p->angle - p->last_angle;				//反转	delta=-
    }
    else 	//angle > last
    {
        res1 = p->angle - 8192 - p->last_angle ;//反转	delta -
        res2 = p->angle - p->last_angle;				//正转	delta +
    }
    //不管正反转，肯定是转的角度小的那个是真的
    if(ABS(res1) < ABS(res2))
        delta = res1;
    else
        delta = res2;

    p->total_angle += delta;
    p->last_angle = p->angle;
}

