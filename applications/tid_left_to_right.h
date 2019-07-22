#ifndef __TID_LEFT_TO_RIGHT
#define __TID_LEFT_TO_RIGHT

#include "mailbox.h"
#include "step.h"
#include "const.h"
#include "dji_pid.h"
#include "calculator.h"

static rt_thread_t tid_left_to_right = RT_NULL;

void left_to_right_init(void);
#endif
