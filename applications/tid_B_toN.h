#ifndef __TID_B_TON
#define __TID_B_TON

#include "mailbox.h"
#include "step.h"
#include "const.h"
#include "dji_pid.h"
#include "calculator.h"

static rt_thread_t tid_B_toN = RT_NULL;

void B_toN_init(void);
#endif
