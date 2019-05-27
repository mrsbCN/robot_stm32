#ifndef __CALCULATER
#define __CALCULATER

#include "mailbox.h"
#include "dji_pid.h"
#include "drv_can.h"
#include <stdlib.h>
#include "ADRC.h"
//#define LOG_TAG              "can"
//#define LOG_LVL              LOG_LVL_DBG
//#include "ulog.h"


/*CAN发送或是接收的ID*/
//typedef enum
//{
//
//	CAN_2006Moto_ALL_ID = 0x200,
//	CAN_2006Moto1_ID = 0x201,
//	CAN_2006Moto2_ID = 0x202,
//	
//}CAN_Message_ID;


#define FILTER_BUF_LEN		5
/*接收到的云台电机的参数结构体*/
typedef struct{
	rt_int16_t	 	speed_rpm;
    float  	real_current;
    rt_int16_t  	given_current;
    rt_uint8_t  	hall;
	rt_uint16_t 	angle;				//abs angle range:[0,8191]
	rt_uint16_t 	last_angle;	//abs angle range:[0,8191]
	rt_uint16_t	offset_angle;
	rt_int32_t		round_cnt;
	rt_int32_t		total_angle;
	rt_uint8_t			buf_idx;
	rt_uint16_t			angle_buf[FILTER_BUF_LEN];
	rt_uint16_t			fited_angle;
	rt_uint32_t			msg_cnt;
}moto_measure_t;

#endif
/* Extern  ------------------------------------------------------------------*/
extern moto_measure_t  moto_chassis[];
extern PID_TypeDef motor_pid[];
extern void reset_total_angle(moto_measure_t *ptr);
