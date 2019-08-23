#ifndef __TIMER_PWM
#define __TIMER_PWM

#include "rtthread.h"
#include "rt_drv_pwm.h"
#include "mailbox.h"
#include "led.h"
#define PWM_DEV_NAME        "pwm8"  /* PWM�豸���� */
#define PWM_LEFT    		1       /* PWMͨ�� */
#define PWM_RIGHT   		2       /* PWMͨ�� */

static rt_thread_t tid_timer_pwm = RT_NULL;

extern struct rt_device_pwm *pwm_dev_left,*pwm_dev_right;      /* PWM�豸��� */   
extern rt_uint32_t period, pulse_l,pulse_r;
extern void timer_pwm_init(void);
#endif
