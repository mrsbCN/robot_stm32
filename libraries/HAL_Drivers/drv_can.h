/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-05     Xeon Xu      the first version
 * 2019-01-22     YLZ          port from stm324xx-HAL to bsp stm3210x-HAL
 * 2019-01-26     YLZ          redefine `struct stm32_drv_can` add member `Rx1Message`
 * 2019-02-19     YLZ          port to BSP [stm32]
 */
#ifndef __DRV_CAN_H__
#define __DRV_CAN_H__
#include "board.h"
#include <rtdevice.h>
#include <rthw.h>
#include <rtthread.h>
#include "mailbox.h"
#define LED1_Pin GPIO_PIN_14
#define LED1_GPIO_Port GPIOF

#define BS1SHIFT 16
#define BS2SHIFT 20
#define RRESCLSHIFT 0
#define SJWSHIFT 24
#define BS1MASK ( (0x0F) << BS1SHIFT )
#define BS2MASK ( (0x07) << BS2SHIFT )
#define RRESCLMASK ( 0x3FF << RRESCLSHIFT )
#define SJWMASK ( 0x3 << SJWSHIFT )

struct stm_baud_rate_tab
{
    rt_uint32_t baud_rate;
    rt_uint32_t confdata;
};

/* STM32 can driver */
struct stm32_drv_can
{
    CAN_HandleTypeDef CanHandle;
    CanTxMsgTypeDef TxMessage;
    CanRxMsgTypeDef RxMessage;
    CanRxMsgTypeDef Rx1Message;
    CAN_FilterConfTypeDef FilterConfig;
};

typedef enum
{

	CAN_2006Moto_ALL_ID = 0x200,
	CAN_2006Moto1_ID = 0x201,
	CAN_2006Moto2_ID = 0x202,
	//CAN_2006Moto3_ID = 0x203,
	//CAN_2006Moto4_ID = 0x204,
	
}CAN_Message_ID;

#ifdef __cplusplus
 extern "C" {
#endif
extern int rt_hw_can_init(void);
extern struct rt_can_device dev_can1;
#ifdef __cplusplus
 }
#endif
#endif /*__DRV_CAN_H__ */
