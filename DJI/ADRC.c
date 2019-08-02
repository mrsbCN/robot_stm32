#include "ADRC.h"
Fhan_Data ADRC_SPEED[2]={0};
const float ADRC_Unit[2][15]=
{
/*TD跟踪微分器   改进最速TD,h0=N*h      扩张状态观测器ESO           扰动补偿     非线性组合*/
/*  r     h      N0                  beta_01   beta_02    beta_03     b0      beta_1      beta_2      alpha1  alpha2  zeta */
 {30000 ,0.05 , 5,               	30,      	300,      1000,      100,    	1600,      	80,     		0.8,   1.5,    0.03},
 {30000 ,0.05 , 5,               	30,      	300,      1000,      100,    	1600,      	80,     		0.8,   1.5,    0.03},
};
//状态观测器参数beta01=1/h  beta02=1/(3*h^2)  beta03=2/(8^2*h^3) ...

float Constrain_Float(float amt, float low, float high){
  return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

rt_int16_t Sign_ADRC(float Input)
{
    rt_int16_t output=0;
    if(Input>1E-6) output=1;
    else if(Input<-1E-6) output=-1;
    else output=0;
    return output;
}

rt_int16_t Fsg_ADRC(float x,float d)
{
  rt_int16_t output=0;
  output=(Sign_ADRC(x+d)-Sign_ADRC(x-d))/2;
  return output;
}
void ADRC_Init(Fhan_Data *fhan_Input1,Fhan_Data *fhan_Input2)
{
	fhan_Input1->r=ADRC_Unit[0][0];
	fhan_Input1->h=ADRC_Unit[0][1];
	fhan_Input1->N0=(rt_uint16_t)(ADRC_Unit[0][2]);
	fhan_Input1->h0=fhan_Input1->h*fhan_Input1->N0;
	fhan_Input1->beta_01=ADRC_Unit[0][3];
	fhan_Input1->beta_02=ADRC_Unit[0][4];
	fhan_Input1->beta_03=ADRC_Unit[0][5];
	fhan_Input1->b0=ADRC_Unit[0][6];
	fhan_Input1->beta_1=ADRC_Unit[0][7];
	fhan_Input1->beta_2=ADRC_Unit[0][8];

	fhan_Input1->alpha1=ADRC_Unit[0][9];
	fhan_Input1->alpha2=ADRC_Unit[0][10];
	fhan_Input1->zeta=ADRC_Unit[0][11];
	
	fhan_Input2->r=ADRC_Unit[1][0];
	fhan_Input2->h=ADRC_Unit[1][1];
	fhan_Input2->N0=(rt_uint16_t)(ADRC_Unit[1][2]);
	fhan_Input2->h0=fhan_Input2->h*fhan_Input2->N0;
	fhan_Input2->beta_01=ADRC_Unit[1][3];
	fhan_Input2->beta_02=ADRC_Unit[1][4];
	fhan_Input2->beta_03=ADRC_Unit[1][5];
	fhan_Input2->b0=ADRC_Unit[1][6];
	fhan_Input2->beta_1=ADRC_Unit[1][7];
	fhan_Input2->beta_2=ADRC_Unit[1][8];
	
	fhan_Input2->alpha1=ADRC_Unit[1][9];
	fhan_Input2->alpha2=ADRC_Unit[1][10];
	fhan_Input2->zeta=ADRC_Unit[1][11];
	
}

//fhan
float Fhan_ADRC(float x1,float x2,float r,float h0)
{
	float d=0,a0=0,y=0,a1=0,a2=0,a=0,fh=0;
	d=r*h0*h0;//d=rh^2;
	a0=h0*x2;//a0=h*x2
	y=x1+a0;//y=x1+a0
	a1=sqrt(d*(d+8*ABS(y)));//a1=sqrt(d*(d+8*ABS(y))])
	a2=a0+Sign_ADRC(y)*(a1-d)/2;//a2=a0+sign(y)*(a1-d)/2;
	a=(a0+y)*Fsg_ADRC(y,d)+a2*(1-Fsg_ADRC(y,d));
	fh=-r*(a/d)*Fsg_ADRC(a,d) - r*Sign_ADRC(a)*(1-Fsg_ADRC(a,d));//得到最速微分加速度跟踪量
	return fh;
}

//ADRC最速跟踪微分器TD
void TD_ADRC(Fhan_Data *fhan_Input,float expect_ADRC)
{
	//fhan_Input->fh = -fhan_Input->r*fhan_Input->r*(fhan_Input->v1 - expect_ADRC)+2*fhan_Input->r*fhan_Input->v2;
	fhan_Input->fh = Fhan_ADRC(fhan_Input->v1 - expect_ADRC,fhan_Input->v2,fhan_Input->r,fhan_Input->h0);
	fhan_Input->v1 += fhan_Input->h*fhan_Input->v2;//跟新最速跟踪状态量v1
	fhan_Input->v2 += fhan_Input->h*fhan_Input->fh;//跟新最速跟踪状态量微分v2
}

//原点附近有连线性段的连续幂次函数
float Fal_ADRC(float e,float alpha,float zeta)
{
    rt_int16_t fsg=0,fdb=0;
    float fal_output=0;
    fsg=(Sign_ADRC(e+zeta)-Sign_ADRC(e-zeta))/2;
	fdb=(Sign_ADRC(e+zeta)+Sign_ADRC(e-zeta))/2;
    fal_output=e*fsg/(powf(zeta,1-alpha))+powf(ABS(e),alpha)*Sign_ADRC(e)*ABS(fdb);
    return fal_output;
}




/************扩张状态观测器********************/
//状态观测器参数beta01=1/h  beta02=1/(3*h^2)  beta03=2/(8^2*h^3) ...
void ESO_ADRC(Fhan_Data *fhan_Input)
{
	
	fhan_Input->e = fhan_Input->z1-fhan_Input->y;//状态误差
	fhan_Input->z1 += fhan_Input->h*(fhan_Input->z2-fhan_Input->beta_01*fhan_Input->e);
	fhan_Input->z2+=fhan_Input->h*(fhan_Input->z3
                                   -fhan_Input->beta_02*fhan_Input->e
                                   +fhan_Input->b*fhan_Input->u);
	fhan_Input->z3+=fhan_Input->h*(-fhan_Input->beta_03*fhan_Input->e);
	
  //fhan_Input->fe=Fal_ADRC(fhan_Input->e,0.5,fhan_Input->h);//非线性函数，提取跟踪状态与当前状态误差
  //fhan_Input->fe1=Fal_ADRC(fhan_Input->e,0.25,fhan_Input->h);
  //
  ///*************扩展状态量更新**********/
  //fhan_Input->z1+=fhan_Input->h*(fhan_Input->z2-fhan_Input->beta_01*fhan_Input->e);
  //fhan_Input->z2+=fhan_Input->h*(fhan_Input->z3
  //                               -fhan_Input->beta_02*fhan_Input->fe
  //                                 +fhan_Input->b*fhan_Input->u);
  //fhan_Input->z3+=fhan_Input->h*(-fhan_Input->beta_03*fhan_Input->fe1);
}
/*
void Nolinear_Conbination_ADRC(Fhan_Data *fhan_Input)
{
  //float temp_e2=0;
  //temp_e2=Constrain_Float(fhan_Input->e2,-3000,3000);
  fhan_Input->u0=fhan_Input->beta_1*Fal_ADRC(fhan_Input->e1,fhan_Input->alpha1,fhan_Input->zeta)
                +fhan_Input->beta_2*Fal_ADRC(fhan_Input->e2,fhan_Input->alpha2,fhan_Input->zeta);

}*/

void ADRC_Control(Fhan_Data *fhan_Input,float expect_ADRC,float feedback_ADRC)
{
	
	/*自抗扰控制器第1步*/
	/*****
	安排过度过程，输入为期望给定，
	由TD跟踪微分器得到：
	过度期望信号v1，过度期望微分信号v2
	******/
	TD_ADRC(fhan_Input,expect_ADRC);
	
	
	/*自抗扰控制器第2步*/

	/************系统输出值为反馈量，状态反馈，ESO扩张状态观测器的输入*********/
	fhan_Input->y=feedback_ADRC;
	/*****
	扩张状态观测器，得到反馈信号的扩张状态：
	1、状态信号z1；
	2、状态速度信号z2；
	3、状态加速度信号z3。
	其中z1、z2用于作为状态反馈与TD微分跟踪器得到的v1,v2做差后，
	经过非线性函数映射，乘以beta系数后，
	组合得到未加入状态加速度估计扰动补偿的原始控制量u
	*********/
	ESO_ADRC(fhan_Input);
	
	/*自抗扰控制器第3步*/
    /********状态误差反馈率***/
    fhan_Input->e1=fhan_Input->v1-fhan_Input->z1;//状态偏差项
    fhan_Input->e2=fhan_Input->v2-fhan_Input->z2;//状态微分项，
	
	fhan_Input->u0=fhan_Input->beta_1*fhan_Input->e1
					-fhan_Input->beta_2*fhan_Input->z2;
	//Nolinear_Conbination_ADRC(fhan_Input);
    /**********扰动补偿*******/
    fhan_Input->u=(fhan_Input->u0-fhan_Input->z3)/fhan_Input->b0;
    fhan_Input->u=Constrain_Float(fhan_Input->u,-10000,10000);//加入扰动补偿
}

