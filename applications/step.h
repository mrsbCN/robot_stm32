#ifndef __STEP
#define __STEP

#include "mailbox.h"
#include "const.h"

extern void forward(rt_int32_t left, rt_int32_t right,rt_int32_t nl, rt_int32_t nr);
extern void backward(rt_int32_t left, rt_int32_t right,rt_int32_t nl, rt_int32_t nr);
extern void for_turnleft(rt_int32_t left, rt_int32_t right,rt_int32_t nl, rt_int32_t nr);
extern void for_turnright(rt_int32_t left, rt_int32_t right,rt_int32_t nl, rt_int32_t nr);
extern void back_turnleft(rt_int32_t left, rt_int32_t right,rt_int32_t nl, rt_int32_t nr);
extern void back_turnright(rt_int32_t left, rt_int32_t right,rt_int32_t nl, rt_int32_t nr);
extern void turnleft(rt_int32_t left, rt_int32_t right,rt_int32_t nl, rt_int32_t nr);
extern void turnright(rt_int32_t left, rt_int32_t right,rt_int32_t nl, rt_int32_t nr);
extern void big_turnleft(rt_int32_t left, rt_int32_t right,rt_int32_t nl, rt_int32_t nr);
extern void big_turnright(rt_int32_t left, rt_int32_t right,rt_int32_t nl, rt_int32_t nr);
extern void stop(void);
#endif
