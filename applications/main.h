#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "led.h"
#include "drv_can.h"
#include "mailbox.h"
#include "calculator.h"
#include "distance.h"
#include "sdcard.h"
#include "tid_chafang.h"
#include "tid_to_a.h"
#include "tid_to_b.h"
#include "string.h"
#include "button.h"
#include "timer_pwm.h"
#include "tid_test.h"
#include "speed_control.h"
//#include "motion_driver_example.h"

extern void cal_init(void);
extern int msgq_init(void);
#define KEY_Pin GPIO_PIN_2
#define KEY_GPIO_Port GPIOB
