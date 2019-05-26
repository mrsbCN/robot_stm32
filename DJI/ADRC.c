#include "ADRC.h"
Fhan_Data ADRC_SPEED[2]={0};
const float ADRC_Unit[2][4]=
{	/* b,			k,			w0,			wc*/    /*beta01=3w0	beta02=3w0^2	beta03=kbeta02*/	/*kp=wc^2	kd=1.3802wc*/
		{400,		4,			10,		40},
		{400,		4,			10,		40},
};


float Constrain_Float(float amt, float low, float high){
  return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

void ADRC_Init(Fhan_Data *fhan_Input,rt_uint8_t num)
{
	for(rt_uint8_t i=0;i<num;i++)
	{
		fhan_Input[i].b = ADRC_Unit[i][0];
		fhan_Input[i].beta_01 = 3*ADRC_Unit[i][2];
		fhan_Input[i].beta_02 = 3*ADRC_Unit[i][2]*ADRC_Unit[i][2];
		fhan_Input[i].beta_03 = ADRC_Unit[i][2]*ADRC_Unit[i][2]*ADRC_Unit[i][2];
		
		fhan_Input[i].kp = ADRC_Unit[i][3]*ADRC_Unit[i][3];
		fhan_Input[i].kd = 2*ADRC_Unit[i][3];
	}

}

void ADRC_Control(Fhan_Data *fhan_Input,float expect_ADRC,float feedback_ADRC)
{

			/*自抗扰控制器第2步*/
      /************系统输出值为反馈量，状态反馈，ESO扩张状态观测器的输入*********/
      fhan_Input->y=feedback_ADRC;
      fhan_Input->e=fhan_Input->z1-fhan_Input->y;//状态误差

			/*************扩展状态量更新**********/
			fhan_Input->z1+=fhan_Input->z2-fhan_Input->beta_01*fhan_Input->e;
			fhan_Input->z2+=fhan_Input->z3-fhan_Input->beta_02*fhan_Input->e+fhan_Input->b*fhan_Input->u;
			fhan_Input->z3+=-fhan_Input->beta_03*fhan_Input->e;
	
			/*自抗扰控制器第3步*/
      /********状态误差反馈率***/
			
      fhan_Input->e1=expect_ADRC-fhan_Input->z1;//状态偏差项
      fhan_Input->e2=-fhan_Input->z2;//状态微分项，
      /********线性组合*******/
     
      fhan_Input->u0=fhan_Input->kp*fhan_Input->e1
                    +fhan_Input->kd*fhan_Input->e2;
      fhan_Input->u=(fhan_Input->u0-fhan_Input->z3)/fhan_Input->b;
      fhan_Input->u=Constrain_Float(fhan_Input->u,-16000,16000);
}

