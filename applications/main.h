#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "led.h"
#include "drv_can.h"
#include "mailbox.h"
#include "calculator.h"
#include "distance.h"
#include "sdcard.h"
#include "drv_spi.h"
#include "tid_to_left.h"
#include "tid_left_to_right.h"
#include "tid_right_to_be.h"
#include "tid_to_right.h"
#include "tid_right_to_left.h"
#include "tid_left_to_be.h"
#include "string.h"
#include "button.h"
#include "timer_pwm.h"
#include "tid_test.h"
//#include "motion_driver_example.h"

extern void cal_init(void);
extern int msgq_init(void);
#define KEY_Pin GPIO_PIN_2
#define KEY_GPIO_Port GPIOB
