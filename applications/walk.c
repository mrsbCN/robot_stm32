#include "walk.h"

static rt_thread_t tid_walk = RT_NULL;


void walk_entry(void * par);
void walk_init(void)
{
	tid_walk = rt_thread_create("walk",walk_entry,RT_NULL,512,10,10);
	if(RT_NULL != tid_walk)
		rt_thread_startup(tid_walk);
}
rt_uint32_t t=0;

void walk_entry(void * par)
{
		struct rt_can_msg msg_send;
		msg_send.id = 0x200;
		msg_send.ide = CAN_ID_STD;
		msg_send.rtr = CAN_RTR_DATA;
		msg_send.len = 0x08;  
		rt_uint32_t e;
		rt_int16_t left_ele,right_ele;
    while(1)
    {
			
			//if (RT_EOK == rt_event_recv(&event,(EVENT_FLAG1 | EVENT_FLAG2),RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER ,&e))
			{
			//rt_mb_recv(&lf_ele_mb,(rt_ubase_t*)&left_ele,RT_WAITING_NO);
			//rt_mb_recv(&ri_ele_mb,(rt_ubase_t*)&right_ele,RT_WAITING_NO);
			msg_send.data[0] =  0x01;//left_ele >>8 ;
			msg_send.data[1] =  0x01;//left_ele;
			msg_send.data[2] =  0x01;//right_ele >>8 ;
			msg_send.data[3] =  0x01;//right_ele;
			msg_send.data[4] =  0;
			msg_send.data[5] = 	0;
			msg_send.data[6] =  0;
			msg_send.data[7] = 	0;
			dev_can1.ops->sendmsg(&dev_can1,&msg_send,CAN_TXMAILBOX_0);
			rt_thread_mdelay(5);
			//rt_kprintf("delt=%d\n",(rt_tick_get()-t));
			//t = rt_tick_get();	
			}
	}
}
