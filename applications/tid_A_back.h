#ifndef __TID_A_BACK
#define __TID_A_BACK

#include "mailbox.h"
#include "step.h"
#include "const.h"
#include "dji_pid.h"
#include "calculator.h"

static rt_thread_t tid_A_back = RT_NULL;

void A_back_init(void);
#endif
