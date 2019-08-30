#ifndef __TID_TO_RIGHT
#define __TID_TO_RIGHT

#include "mailbox.h"
#include "step.h"
#include "const.h"
#include "dji_pid.h"
#include "calculator.h"
#include "led.h"
#include "timer_pwm.h"
static rt_thread_t tid_to_right = RT_NULL;

void to_right_init(void);
#endif
