#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "led.h"
#include "drv_can.h"
#include "mailbox.h"
#include "calculator.h"
#include "distance.h"
#include "cpuusage.h"
#include "sdcard.h"
#include "drv_spi.h"
#include "tid_toR.h"
#include "string.h"
//#include "motion_driver_example.h"

extern void cal_init(void);
extern int msgq_init(void);
#define KEY_Pin GPIO_PIN_2
#define KEY_GPIO_Port GPIOB
