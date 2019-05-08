#include "moto2.h"

static rt_thread_t tid_moto = RT_NULL;
PID_TypeDef motor_pid[4];
int32_t set_spd = 500;
void moto_entry(void * par);
void moto_init(void)
{
    rt_hw_can_init();
		struct can_configure cfg;
		cfg.baud_rate = CAN1MBaud;
		cfg.msgboxsz = RT_CANMSG_BOX_SZ;
		cfg.sndboxnumber = RT_CANSND_BOX_NUM;
		cfg.mode = NORMAL;
		cfg.privmode = 0;
		dev_can1.ops->configure(&dev_can1,&cfg);
		tid_moto = rt_thread_create("moto",moto_entry,RT_NULL,512,25,10);
		if(RT_NULL != tid_moto)
			rt_thread_startup(tid_moto);
}

void moto_entry(void * par)
{
	int32_t set_spd = 500;
	struct rt_can_msg msg_send;
	
	dev_can1.ops->control(&dev_can1,RT_DEVICE_CTRL_SET_INT,(void *)RT_DEVICE_FLAG_INT_RX);
	  for(int i=0; i<4; i++)
  {	

    pid_init(&motor_pid[i]);
    motor_pid[i].f_param_init(&motor_pid[i],PID_Speed,16384,5000,10,0,8000,0,1.5,0.1,0);
    
  }
	msg_send.id = 0x200;
	msg_send.ide = CAN_ID_STD;
	msg_send.rtr = CAN_RTR_DATA;
	msg_send.len = 0x08;	
	while (1)
	{	
		
    for(int i=0; i<4; i++)
    {	
      motor_pid[i].target = set_spd; 																							
      motor_pid[i].f_cal_pid(&motor_pid[i],100);    //根据设定值进行PID计算。
    }
		msg_send.data[0] =  ((rt_int16_t)motor_pid[0].output) >>8 ;
		msg_send.data[1] = 	((rt_int16_t)motor_pid[0].output);
		msg_send.data[2] =  ((rt_int16_t)motor_pid[1].output) >>8 ;
		msg_send.data[3] = 	((rt_int16_t)motor_pid[1].output);
		msg_send.data[4] =  ((rt_int16_t)motor_pid[2].output) >>8 ;
		msg_send.data[5] = 	((rt_int16_t)motor_pid[2].output);
		msg_send.data[6] =  ((rt_int16_t)motor_pid[3].output) >>8 ;
		msg_send.data[7] = 	((rt_int16_t)motor_pid[3].output);
		dev_can1.ops->sendmsg(&dev_can1,&msg_send,CAN_FIFO0);

		rt_thread_mdelay(11);
	}
}
