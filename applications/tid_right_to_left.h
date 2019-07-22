#ifndef __TID_RIGHT_TO_LEFT
#define __TID_RIGHT_TO_LEFT

#include "mailbox.h"
#include "step.h"
#include "const.h"
#include "dji_pid.h"
#include "calculator.h"

static rt_thread_t tid_right_to_left = RT_NULL;

void right_to_left_init(void);
#endif
