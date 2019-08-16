#ifndef __SPEED_CONTROL
#define __SPEED_CONTROL

#include "mailbox.h"
#include "ADRC.h"
#include "kalman.h"
#include "arm_math.h"
#include "drv_can.h"

void speed_control_init(void);
#endif
