#ifndef __TID_NURSE
#define __TID_NURSE

#include "mailbox.h"
#include "const.h"
#include "dji_pid.h"
#include "calculator.h"

static rt_thread_t tid_tonurse = RT_NULL;

void tonurse_init(void);
#endif
