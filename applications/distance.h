#ifndef __DISTANCE
#define __DISTANCE
#include "mailbox.h"
#include <stdlib.h>
#include <arm_math.h>
#include <math.h>
#define K   0.0013315      //(3.1415*125/8192/36)     //总角度-->距离(mm)系数 pi，轮子直径，一圈信号数，减速比

static rt_thread_t tid_dis = RT_NULL;
static rt_thread_t tid_dis_turn = RT_NULL;
#endif
extern void dis_init(void);
