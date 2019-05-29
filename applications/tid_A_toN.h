#ifndef __TID_A_TON
#define __TID_A_TON

#include "mailbox.h"
#include "step.h"
#include "const.h"
#include "dji_pid.h"
#include "calculator.h"

static rt_thread_t tid_A_toN = RT_NULL;

void A_toN_init(void);
#endif
