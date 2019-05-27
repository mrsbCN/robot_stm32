#ifndef __STEP
#define __STEP

#include "mailbox.h"
#include "const.h"

extern void forward(rt_int32_t left, rt_int32_t right);
extern void backward(rt_int32_t left, rt_int32_t right);
extern void for_turnleft(rt_int32_t left, rt_int32_t right);
extern void for_turnright(rt_int32_t left, rt_int32_t right);
extern void back_turnleft(rt_int32_t left, rt_int32_t right);
extern void back_turnright(rt_int32_t left, rt_int32_t right);
extern void stop(void);
#endif
