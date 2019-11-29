#ifndef __TID_CHAFANG
#define __TID_CHAFANG

#include "mailbox.h"
#include "step.h"
#include "const.h"
#include "dji_pid.h"
#include "calculator.h"
#include "led.h"
#include "timer_pwm.h"

static rt_thread_t tid_chafang = RT_NULL;

void chafang_init(void);
#endif
