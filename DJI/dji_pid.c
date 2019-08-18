/**
  ******************************************************************************
  * @file    pid.c
  * @author  Ginger
  * @version V1.0.0
  * @date    2015/11/14
  * @brief   对每一个pid结构体都要先进行函数的连接，再进行初始化
  ******************************************************************************
  * @attention 应该是用二阶差分(d)云台会更加稳定
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "dji_pid.h"
#include "stm32f4xx.h"

#define ABS(x)		((x>0)? x: -x) 

/*参数初始化--------------------------------------------------------------*/
static void pid_param_init(
	PID_TypeDef * pid, 
	PID_ID   id,
	rt_uint16_t maxout,
	rt_uint16_t intergral_limit,
	float deadband,
	rt_uint16_t period,
	rt_int16_t  max_err,
	rt_int16_t  target,

	float 	kp, 
	float 	ki, 
	float 	kd)
{
	pid->id = id;		
	
	//pid->ControlPeriod = period;             //没用到
	pid->DeadBand = deadband;
	pid->IntegralLimit = intergral_limit;
	pid->MaxOutput = maxout;
	pid->Max_Err = max_err;
	pid->target = target;
	
	pid->kp = kp;
	pid->ki = ki;
	pid->kd = kd;
	
	pid->output = 0;
}

/*中途更改参数设定--------------------------------------------------------------*/
static void pid_reset(PID_TypeDef * pid)
{

	pid->measure = 0;					//测量值
	pid->err=0;							//误差
	pid->last_err=0;      		//上次误差
	pid->pout=0;
	pid->iout=0;
	pid->dout=0;
	pid->output=0;						//本次输出
	pid->last_output=0;			//上次输出
	
}

/*pid计算-----------------------------------------------------------------------*/

	
static float pid_calculate(PID_TypeDef* pid, float measure)//, int16_t target)
{
	//uint32_t time,lasttime;
	
	//pid->lasttime = pid->thistime;
	//pid->thistime = rt_tick_get();
	//pid->dtime = pid->thistime-pid->lasttime;
	pid->measure = measure;
  //	pid->target = target;
		
	pid->last_err  = pid->err;
	pid->last_output = pid->output;
	
	pid->err = pid->target - pid->measure;
	
	
	//是否进入死区
	if((ABS(pid->err) > pid->DeadBand))
	{
		pid->pout = pid->kp * pid->err;
		pid->iout += (pid->ki * pid->err);
		

		pid->dout =  pid->kd * (pid->err - pid->last_err); 
		
		//积分是否超出限制
		if(pid->iout > pid->IntegralLimit)
			pid->iout = pid->IntegralLimit;
		if(pid->iout < - pid->IntegralLimit)
			pid->iout = - pid->IntegralLimit;
		
		//pid输出和
		pid->output = pid->pout + pid->iout + pid->dout;
		

		//pid->output = pid->output*0.7f + pid->last_output*0.3f;  //滤波？
		if(pid->output > pid->MaxOutput)         
		{
			pid->output = pid->MaxOutput;
		}
		if(pid->output < -(pid->MaxOutput))
		{
			pid->output = -(pid->MaxOutput);
		}
	
	}


	return pid->output;
}

/*pid结构体初始化，每一个pid参数需要调用一次-----------------------------------------------------*/
void pid_init(PID_TypeDef* pid)
{
	pid->f_param_init = pid_param_init;
	pid->f_pid_reset = pid_reset;
	pid->f_cal_pid = pid_calculate;
}
