#ifndef __TID_TO_B
#define __TID_TO_B

#include "mailbox.h"
#include "step.h"
#include "const.h"
#include "dji_pid.h"
#include "calculator.h"
#include "led.h"
#include "timer_pwm.h"

static rt_thread_t tid_to_B = RT_NULL;

void to_B_init(void);
#endif
