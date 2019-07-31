#include "timer.h"

void timer_entry(void *par)
{
	while(1)
	{
		if(RT_EOK == rt_event_recv(&event_pwm, EVENT_PWM_LEFT|EVENT_PWM_RIGHT|EVENT_PWM_CAM, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))	//����յ�dist�¼���ʼ����
        {
			if(recved == EVENT_PWM_LEFT)
			{
				if(pulse_l == 500000)
				{
					rt_pin_write(SPEAKER1_PIN, PIN_LOW);
					for(rt_uint8_t i =0;i<10;i++)
					{
						pulse_l += 200000;
						rt_pwm_set(pwm_dev_left, PWM_LEFT, period, pulse_l);
						rt_thread_mdelay(5);
					}
				}
				else if(pulse_l == 2500000)
				{
					for(rt_uint8_t i =0;i<10;i++)
					{
						pulse_l -= 200000;
						rt_pwm_set(pwm_dev_left, PWM_LEFT, period, pulse_l);
						rt_thread_mdelay(5);
					}
				}
			}
			if(recved == EVENT_PWM_RIGHT)
			{
				if(pulse_r == 500000)
				{
					rt_pin_write(SPEAKER2_PIN, PIN_LOW);
					for(rt_uint8_t i =0;i<10;i++)
					{
						pulse_l += 200000;
						rt_pwm_set(pwm_dev_right, PWM_RIGHT, period, pulse_r);
						rt_thread_mdelay(5);
					}
				}
				else if(pulse_l == 2500000)
				{
					for(rt_uint8_t i =0;i<10;i++)
					{
						pulse_l -= 200000;
						rt_pwm_set(pwm_dev_right, PWM_RIGHT, period, pulse_r);
						rt_thread_mdelay(5);
					}
				}
			}
			
		}
		
	}
}

void timer_init(void)
{
	period = 20000000;  //��λns
	pulse_l =  500000;	/* PWM�������ֵ����λΪ����ns */ //��ʱ����0���ǹر�
	pulse_r =  500000;
	pwm_dev_left = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
	rt_pwm_set(pwm_dev_left, PWM_LEFT, period, pulse_l);
	rt_pwm_enable(pwm_dev_left, PWM_LEFT);
	pwm_dev_right = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
	rt_pwm_set(pwm_dev_right, PWM_RIGHT, period, pulse_r);
	rt_pwm_enable(pwm_dev_left, PWM_RIGHT);
	
	tid_timer = rt_thread_create("tid_timer",
                                   timer_entry, RT_NULL,
                                   2048 ,
                                   8 , 10);		//���ȼ���һЩ
    if(tid_timer != RT_NULL)
        rt_thread_startup(tid_timer);
}