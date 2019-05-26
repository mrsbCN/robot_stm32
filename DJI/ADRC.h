#include <rtthread.h>
#include <math.h>

#define ABS(x)	( (x>0) ? (x) : (-x) )

#ifndef _ADRC_H_
#define _ADRC_H_

typedef struct
{
/*****安排过度过程*******/
float x1;//跟踪微分期状态量
float x2;//跟踪微分期状态量微分项


/*****扩张状态观测器*******/
/******已系统输出y和输入u来跟踪估计系统状态和扰动*****/
float z1;
float z2;
float z3;//根据控制对象输入与输出，提取的扰动信息
float e;//系统状态误差
float y;//系统输出量
float beta_01;
float beta_02;
float beta_03;
float b;


/**********系统状态误差反馈率*********/
float e0;//状态误差积分项
float e1;//状态偏差
float e2;//状态量微分项
float u0;//非线性组合系统输出
float u;//带扰动补偿后的输出

/*********线性组合形式*********/
float ki;
float kp;
float kd;//u0=kp*e1+kd*e2+(beta_ki*e0);



}Fhan_Data;



void ADRC_Init(Fhan_Data *fhan_Input1,rt_uint8_t num);
void ADRC_Control(Fhan_Data *fhan_Input,float expect_ADRC,float feedback);

extern Fhan_Data ADRC_SPEED[];
#endif

