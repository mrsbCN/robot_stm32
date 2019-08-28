#ifndef __TID_LEFT_TO_BE
#define __TID_LEFT_TO_BE

#include "mailbox.h"
#include "step.h"
#include "const.h"
#include "dji_pid.h"
#include "calculator.h"
#include "led.h"
static rt_thread_t tid_left_to_be = RT_NULL;

void left_to_be_init(void);
#endif
