#include "deviation.h"


static rt_thread_t tid_deviation = RT_NULL;

void deviation_entry(void *par);

float ADRC_Unit1[2][15]=
{
/*TD跟踪微分器   改进最速TD,h0=N*h      扩张状态观测器ESO(w0=4wc)           扰动补偿     			非线性组合(wc)*/
/*  r     h      	N0                 beta_01   beta_02    beta_03     	b0      	beta_0			beta_1      beta_2      alpha1  alpha2  zeta */
 {3000 ,0.005 , 	20,               	100,      	300,      1000,      	60,    		0.005,			400,      	20,     		0.8,   1.5,    0.03},
 {3000 ,0.005 , 	20,               	100,      	300,      1000,      	60,    		0.005,			400,      	20,     		0.8,   1.5,    0.03},
};

void deviation_init(void)
{

    tid_deviation = rt_thread_create("deviation", deviation_entry, RT_NULL, 4096, 20, 20);

    if(RT_NULL != tid_deviation)
        rt_thread_startup(tid_deviation);
}

void deviation_entry(void *par)
{

}

