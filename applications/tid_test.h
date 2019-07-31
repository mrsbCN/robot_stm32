#ifndef __TID_TEST
#define __TID_TEST

#define EVENT_TEST (1 << 0)		//Ã¿´Î
#include "rtthread.h"
#include "mailbox.h"
static rt_thread_t tid_test = RT_NULL;
void test_init(void);
#endif
