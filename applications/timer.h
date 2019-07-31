#ifndef __MYTIMER
#define __MYTIMER

#include "rtthread.h"
#include "rt_drv_pwm.h"
#include "mailbox.h"
#include "led.h"
#define PWM_DEV_NAME        "pwm8"  /* PWM设备名称 */
#define PWM_LEFT    		1       /* PWM通道 */
#define PWM_RIGHT   		2       /* PWM通道 */

static rt_thread_t tid_timer = RT_NULL;

struct rt_device_pwm *pwm_dev_left,*pwm_dev_right;      /* PWM设备句柄 */   
rt_uint32_t period, pulse_l,pulse_r;
rt_uint32_t recved;
void timer_init(void);
#endif
