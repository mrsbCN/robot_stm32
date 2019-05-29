#ifndef __TID_A_TOM
#define __TID_A_TOM

#include "mailbox.h"
#include "step.h"
#include "const.h"
#include "dji_pid.h"
#include "calculator.h"

static rt_thread_t tid_A_toM = RT_NULL;

void A_toM_init(void);
#endif
