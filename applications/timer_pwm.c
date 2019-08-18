#include "timer_pwm.h"


struct rt_device_pwm *pwm_dev_left,*pwm_dev_right;
rt_uint32_t period, pulse_l,pulse_r;
rt_uint32_t recved;

void timer_pwm_entry(void *par)
{
	while(1)
	{
		if(RT_EOK == rt_event_recv(&event_pwm, EVENT_PWM_LEFT|EVENT_PWM_RIGHT|EVENT_PWM_CAM, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))	//如果收到dist事件则开始计算
        {
			if(recved == EVENT_PWM_LEFT)
			{
				if(pulse_l == 2700000)
				{
					rt_pin_write(SPEAKER1_PIN, PIN_LOW);
					for(rt_uint8_t i =0;i<5;i++)
					{
						pulse_l += 200000;
						rt_pwm_set(pwm_dev_left, PWM_LEFT, period, pulse_l);
						rt_thread_mdelay(5);
					}
					rt_pin_write(SPEAKER1_PIN, PIN_HIGH);
				}
				else if(pulse_l == 3700000)
				{
					for(rt_uint8_t i =0;i<5;i++)
					{
						pulse_l -= 200000;
						rt_pwm_set(pwm_dev_left, PWM_LEFT, period, pulse_l);
						rt_thread_mdelay(5);
					}
				}
			}
			if(recved == EVENT_PWM_RIGHT)
			{
				if(pulse_r == 2400000)
				{
					rt_pin_write(SPEAKER2_PIN, PIN_LOW);
					for(rt_uint8_t i =0;i<8;i++)
					{
						pulse_l -= 200000;
						rt_pwm_set(pwm_dev_right, PWM_RIGHT, period, pulse_r);
						rt_thread_mdelay(5);
					}
					rt_pin_write(SPEAKER2_PIN, PIN_HIGH);
				}
				else if(pulse_l == 800000)
				{
					for(rt_uint8_t i =0;i<10;i++)
					{
						pulse_l += 200000;
						rt_pwm_set(pwm_dev_right, PWM_RIGHT, period, pulse_r);
						rt_thread_mdelay(5);
					}
				}
			}
			
		}
		
	}
}

void timer_pwm_init(void)
{
	period = 20000000;  //单位ns
	pulse_l = 2700000;	/* PWM脉冲宽度值，单位为纳秒ns */
	pulse_r = 2400000;
	pwm_dev_left = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
	rt_pwm_set(pwm_dev_left, PWM_LEFT, period, pulse_l);
	rt_pwm_enable(pwm_dev_left, PWM_LEFT);
	pwm_dev_right = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
	rt_pwm_set(pwm_dev_right, PWM_RIGHT, period, pulse_r);
	rt_pwm_enable(pwm_dev_left, PWM_RIGHT);
	
	tid_timer_pwm = rt_thread_create("tid_timer_pwm",
                                   timer_pwm_entry, RT_NULL,
                                   2048 ,
                                   8 , 10);		//优先级高一些
    if(tid_timer_pwm != RT_NULL)
        rt_thread_startup(tid_timer_pwm);
}
