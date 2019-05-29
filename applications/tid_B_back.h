#ifndef __TID_B_BACK
#define __TID_B_BACK

#include "mailbox.h"
#include "step.h"
#include "const.h"
#include "dji_pid.h"
#include "calculator.h"

static rt_thread_t tid_B_back = RT_NULL;

void B_back_init(void);
#endif
