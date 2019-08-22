#ifndef __STEP
#define __STEP

#include "mailbox.h"
#include "const.h"

extern void forward(rt_int32_t left, rt_int32_t right,rt_int32_t nl, rt_int32_t nr);
extern void backward(rt_int32_t left, rt_int32_t right,rt_int32_t nl, rt_int32_t nr);
extern void stop(void);
extern void stop_to_for(void);
extern void stop_to_back(void);
#endif
