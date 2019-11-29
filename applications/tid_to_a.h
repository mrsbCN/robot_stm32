#ifndef __TID_TO_A
#define __TID_TO_A

#include "mailbox.h"
#include "step.h"
#include "const.h"
#include "dji_pid.h"
#include "calculator.h"
#include "led.h"
#include "timer_pwm.h"

static rt_thread_t tid_to_A = RT_NULL;

void to_A_init(void);
#endif
