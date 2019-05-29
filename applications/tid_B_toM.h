#ifndef __TID_B_TOM
#define __TID_B_TOM

#include "mailbox.h"
#include "step.h"
#include "const.h"
#include "dji_pid.h"
#include "calculator.h"

static rt_thread_t tid_B_toM = RT_NULL;

void B_toM_init(void);
#endif
