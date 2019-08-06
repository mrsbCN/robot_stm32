#ifndef __TID_TEST
#define __TID_TEST

#define EVENT_TEST (1 << 0)

#include "mailbox.h"
#include "step.h"
#include "const.h"
#include "dji_pid.h"
#include "calculator.h"

static rt_thread_t tid_test = RT_NULL;

void test_init(void);
#endif
