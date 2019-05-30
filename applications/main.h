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
#include "tid_chatoM.h"
#include "tid_chatoN.h"
#include "tid_chaback.h"
#include "tid_tonurse.h"
#include "tid_A_toM.h"
#include "tid_A_Mtonurse.h"
#include "tid_A_toN.h"
#include "tid_A_back.h"
#include "tid_B_toM.h"
#include "tid_B_Ntonurse.h"
#include "tid_B_toN.h"
#include "tid_B_back.h"
#include "string.h"
#include "button.h"
//#include "motion_driver_example.h"

extern void cal_init(void);
extern int msgq_init(void);
#define KEY_Pin GPIO_PIN_2
#define KEY_GPIO_Port GPIOB
