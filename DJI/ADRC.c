#include "ADRC.h"
Fhan_Data ADRC_SPEED[2]={0};


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

rt_int16_t Fdb_ADRC(float x,float d)
{
  rt_int16_t output=0;
  output=Sign_ADRC(x)*(Sign_ADRC(x+d)+Sign_ADRC(x-d))/2;
  return output;
}

void ADRC_Init(Fhan_Data *fhan_Input,float ADRC_Unit[][15])
{
	for (rt_uint8_t i=0;i<2;i++)
	{
		fhan_Input[i].r=ADRC_Unit[i][0];
		fhan_Input[i].h=ADRC_Unit[i][1];
		fhan_Input[i].N0=(rt_uint16_t)(ADRC_Unit[i][2]);
		fhan_Input[i].h0=fhan_Input[i].h*fhan_Input[i].N0;
		fhan_Input[i].beta_01=ADRC_Unit[i][3];
		fhan_Input[i].beta_02=ADRC_Unit[i][4];
		fhan_Input[i].beta_03=ADRC_Unit[i][5];
		fhan_Input[i].b0=ADRC_Unit[i][6];
		fhan_Input[i].beta_0=ADRC_Unit[i][7];
		fhan_Input[i].beta_1=ADRC_Unit[i][8];
		fhan_Input[i].beta_2=ADRC_Unit[i][9];
		
		fhan_Input[i].alpha1=ADRC_Unit[i][10];
		fhan_Input[i].alpha2=ADRC_Unit[i][11];
		fhan_Input[i].zeta=ADRC_Unit[i][12];
		fhan_Input[i].c = 0;
		fhan_Input[i].e = 0;
		fhan_Input[i].e0 = 0;
		fhan_Input[i].e1 = 0;
		fhan_Input[i].e2 = 0;
		fhan_Input[i].fe = 0;
		fhan_Input[i].fe1 = 0;
		fhan_Input[i].fh = 0;
		fhan_Input[i].u = 0;
		fhan_Input[i].u0 = 0;
		fhan_Input[i].v1 = 0;
		fhan_Input[i].v2 = 0;
		fhan_Input[i].y = 0;
		fhan_Input[i].z1 = 0;
		fhan_Input[i].z2 = 0;
		fhan_Input[i].z3 = 0;
	}
}

//fhan
float Fhan_ADRC(float x1,float x2,float r,float h0)
{
	float d=0,a0=0,y=0,a1=0,a2=0,a=0,fh=0;
	d=r*h0*h0;//d=rh^2;
	a0=h0*x2;//a0=h*x2
	y=x1+a0;//y=x1+a0
	arm_sqrt_f32(d*(d+8*ABS(y)),&a1);//a1=sqrt(d*(d+8*ABS(y))])
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
    rt_int16_t fsg=0;
    float fal_output=0;
    fsg=Fdb_ADRC(e,zeta);
    fal_output=e*fsg/(powf(zeta,1-alpha))+powf(ABS(e),alpha)*Sign_ADRC(e)*(1-fsg);
    return fal_output;
}


/************扩张状态观测器********************/
//状态观测器参数beta01=1/h  beta02=1/(3*h^2)  beta03=2/(8^2*h^3) ...
void ESO_ADRC(Fhan_Data *fhan_Input)
{
	
	fhan_Input->e = fhan_Input->z1-fhan_Input->y;//状态误差
	
	//fhan_Input->z1 += fhan_Input->h*(fhan_Input->z2-fhan_Input->beta_01*fhan_Input->e);
	//fhan_Input->z2 += fhan_Input->h*(fhan_Input->z3
    //                               -fhan_Input->beta_02*fhan_Input->e
    //                              +fhan_Input->b0*fhan_Input->u);
	//fhan_Input->z3 += fhan_Input->h*(-fhan_Input->beta_03*fhan_Input->e);
	
	fhan_Input->fe=Fal_ADRC(fhan_Input->e,0.5,fhan_Input->zeta);//非线性函数，提取跟踪状态与当前状态误差
	fhan_Input->fe1=Fal_ADRC(fhan_Input->e,0.25,fhan_Input->zeta);
	
	/*************扩展状态量更新**********/
	fhan_Input->z1+=fhan_Input->h*(fhan_Input->z2-fhan_Input->beta_01*fhan_Input->e);
	fhan_Input->z2+=fhan_Input->h*(fhan_Input->z3
									-fhan_Input->beta_02*fhan_Input->fe
									+fhan_Input->b0*fhan_Input->u);
	fhan_Input->z3+=fhan_Input->h*(-fhan_Input->beta_03*fhan_Input->fe1);
}


/*完全线性的*/
void ADRC_Control(Fhan_Data *fhan_Input,float expect_ADRC,float feedback_ADRC)
{
	
	/*自抗扰控制器第1步*/
	fhan_Input->v0 = expect_ADRC;
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
    fhan_Input->e0+=fhan_Input->e1*fhan_Input->beta_0;//状态积分项
    fhan_Input->e1=fhan_Input->v1-fhan_Input->z1;//状态偏差项
    fhan_Input->e2= -fhan_Input->z2;//状态微分项，
	
	float temp_e2=0;
	temp_e2=Constrain_Float(fhan_Input->e2,-2000,2000);
	fhan_Input->u0=fhan_Input->beta_1*Fal_ADRC(fhan_Input->e1,fhan_Input->alpha1,fhan_Input->zeta)
                +fhan_Input->beta_2*Fal_ADRC(temp_e2,fhan_Input->alpha2,fhan_Input->zeta);
	
	//fhan_Input->u=(fhan_Input->beta_1*fhan_Input->e1
	//				+fhan_Input->beta_2*fhan_Input->e2
	//				-fhan_Input->z3)/fhan_Input->b0
	//				+fhan_Input->e0;
	fhan_Input->u = (fhan_Input->u0-fhan_Input->z3)/fhan_Input->b0+fhan_Input->e0;
    fhan_Input->u=Constrain_Float(fhan_Input->u,-7000,7000);//加入扰动补偿
}
