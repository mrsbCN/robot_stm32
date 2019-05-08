#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "dji_can.h"
#include "dji_bsp_can.h"
#include "dji_pid.h"

#define SpeedStep 500

static rt_thread_t tid_moto = RT_NULL;
void moto_init(void);