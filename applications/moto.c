#include "moto.h"

void moto_entry(void * par);
void moto_init(void)
{
	MX_CAN1_Init();
	my_can_filter_init_recv_all(&hcan1);
	//HAL_CAN_Receive_IT(&hcan1, CAN_FIFO1);
	
	rt_kprintf("%d",sizeof(PID_TypeDef));
	for(int i=0; i<4; i++)
	{	

		pid_init(&motor_pid[i]);
		motor_pid[i].f_param_init(&motor_pid[i],PID_Speed,16384,5000,10,0,8000,0,1.5,0.1,0);
		
	}

	tid_moto = rt_thread_create("moto",moto_entry,RT_NULL,4096,9,1000);

	if (tid_moto !=RT_NULL)
		rt_thread_startup(tid_moto);
}

void moto_entry(void * par)
{
	int32_t set_spd = 500;
	while (1)
	{	
		
		for(int i=0; i<4; i++)
		{	
			motor_pid[i].target = set_spd;
			motor_pid[i].f_cal_pid(&motor_pid[i],moto_chassis[i].speed_rpm);    
		}
		
		set_moto_current(&hcan1, motor_pid[0].output,
												motor_pid[1].output,
												motor_pid[2].output,
												motor_pid[3].output);
		rt_thread_mdelay(10);

	}
}
