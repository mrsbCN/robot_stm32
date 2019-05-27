#ifndef __LED
#define __LED

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define THREAD_PRIORITY 25
#define THREAD_STACK_SIZE 512
#define THREAD_TIMESLICE 5
#define LED0_PIN    GET_PIN(E, 11)
#define LED1_PIN    GET_PIN(F, 14)
#define POWER1_PIN	GET_PIN(H,	2)
#define POWER2_PIN	GET_PIN(H,	3)
#define KEY1_PIN		GET_PIN(B,	2)
#define SPI5_NSS		GET_PIN(F,	6)
static rt_thread_t tid_led1 = RT_NULL;
static rt_thread_t tid_led2 = RT_NULL;
void led_init(void);

#endif
