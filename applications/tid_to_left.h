#ifndef __TID_TO_LEFT
#define __TID_TO_LEFT

#include "mailbox.h"
#include "step.h"
#include "const.h"
#include "dji_pid.h"
#include "calculator.h"
#include "led.h"
#include "timer_pwm.h"

static rt_thread_t tid_to_left = RT_NULL;

void to_left_init(void);
#endif
