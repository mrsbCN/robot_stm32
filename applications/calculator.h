#ifndef __CALCULATER
#define __CALCULATER

#include "const.h"
#include "mailbox.h"
#include "ADRC.h"
#include "kalman.h"
#include "arm_math.h"
typedef struct
{
    rt_int16_t	 	speed_rpm;
    float  			real_current;
    rt_int16_t  	given_current;
    rt_uint8_t  	hall;
    rt_uint16_t 	angle;				//abs angle range:[0,8191]
    rt_uint16_t 	last_angle;	//abs angle range:[0,8191]
    rt_uint16_t		offset_angle;
    rt_int32_t		round_cnt;
    rt_int32_t		total_angle;
	rt_int32_t		delta_angle;
} moto_measure_t;

#endif
/* Extern  ------------------------------------------------------------------*/
extern moto_measure_t  moto_chassis[];
extern void reset_total_angle(moto_measure_t *ptr);
extern void cal_init(void);
