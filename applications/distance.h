#include "mailbox.h"

#define K   0.0012783      //(3.1415*120/8192/36)     //总角度-->距离(mm)系数

static rt_thread_t tid_dis = RT_NULL;
extern void dis_init(void);
