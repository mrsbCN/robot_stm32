#ifndef __LED
#define __LED

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "button.h"
#include "mailbox.h"

#define THREAD_PRIORITY 25
#define THREAD_STACK_SIZE 512
#define THREAD_TIMESLICE 5
#define LED0_PIN    GET_PIN(E, 11)
#define LED1_PIN    GET_PIN(F, 14)
#define LED2_PIN    GET_PIN(G, 	1)
#define POWER1_PIN	GET_PIN(H,	2)
#define POWER2_PIN	GET_PIN(H,	3)
#define POWERCI_PIN	GET_PIN(H,	4)
#define POWER3_PIN	GET_PIN(G,	13)
#define SPEAKER1_PIN	GET_PIN(F,	0)
#define SPEAKER2_PIN	GET_PIN(E,	4)
#define SPEAKER3_PIN	GET_PIN(F,	1)
#define SPEAKER4_PIN	GET_PIN(E,	5)
#define OPENMV_PIN		GET_PIN(E,	12)
#define KEY1_PIN		GET_PIN(B,	2)
#define KEY_patient		GET_PIN(A,	4)
static rt_thread_t tid_led1 = RT_NULL;
static rt_thread_t tid_led2 = RT_NULL;
static rt_thread_t tid_led3 = RT_NULL;
static Button_t But_patient;
static rt_uint8_t go_patient = 1;
void led_init(void);
extern void wait_for_patient(void);
#endif
