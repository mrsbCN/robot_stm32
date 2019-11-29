/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 */
#include "main.h"
#define AXIS_UART       "uart7"
static rt_device_t serial;
CAN_HandleTypeDef hcan1;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_uart7_rx;
rt_uint8_t status = 0x0;
rt_uint8_t go = 0x1;
void MX_CAN1_Init(void);
void HAL_CAN_MspInit(CAN_HandleTypeDef *canHandle);
void HAL_CAN_MspDeInit(CAN_HandleTypeDef *canHandle);
void can_init(void);
void uart_init(void);
Button_t Button1;

uint8_t Read_KEY1_Level(void) { return rt_pin_read(KEY_patient);}

void Btn1_Dowm_CallBack(void *btn)		//单击开始运行
{
	rt_kprintf("Button1 Click!\n");
	go = 0;
}

void Btn1_Double_CallBack(void *btn)  	//双击切换先去A还是B
{
	rt_kprintf("Button1 Double click!\n");
	if(rt_pin_read(LED2_PIN) ==PIN_HIGH)  
	{
		rt_pin_write(LED2_PIN,PIN_LOW); //低电平亮，先去A
		status = 0;
	}
	else
	{
		rt_pin_write(LED2_PIN,PIN_HIGH);//高电平灭，先去B
		status = 1;
	}
}

int main(void)
{
	msgq_init();
    MX_CAN1_Init();
    can_init();
    led_init();
	uart_init();
	rt_thread_mdelay(1000);
    cal_init();
    dis_init();
	timer_pwm_init();
	speed_control_init();
	Button_Create("Button1",
              &Button1, 
              Read_KEY1_Level, 
              PIN_HIGH);
	Button_Attach(&Button1,BUTTON_DOWM,Btn1_Dowm_CallBack);                       //Click
	Button_Attach(&Button1,BUTTON_DOUBLE,Btn1_Double_CallBack);                   //Double click
    while(go)                            
	{
		Button_Process();
		rt_thread_mdelay(20);
	}
	
	Button_Delete(&Button1);
	rt_mutex_take(&mission_mu, RT_WAITING_FOREVER);
	if(status == 0)
	{
		rt_kprintf("go A first!\n");
		rt_thread_mdelay(1);
		chafang_init();
		rt_thread_mdelay(1);
		to_A_init();
	}
	else if (status == 1)
	{
		rt_kprintf("go B first!\n");
		rt_thread_mdelay(1);
		chafang_init();
		rt_thread_mdelay(1);
		to_B_init();
	}
    rt_mutex_release(&mission_mu);
    return RT_EOK;
}

void MX_CAN1_Init(void)
{

    hcan1.Instance = CAN1;
    hcan1.Init.Prescaler = 3;
    hcan1.Init.Mode = CAN_MODE_NORMAL;
    hcan1.Init.SJW = CAN_SJW_1TQ;
    hcan1.Init.BS1 = CAN_BS1_9TQ;
    hcan1.Init.BS2 = CAN_BS2_4TQ;
    hcan1.Init.TTCM = DISABLE;
    hcan1.Init.ABOM = DISABLE;
    hcan1.Init.AWUM = DISABLE;
    hcan1.Init.NART = DISABLE;
    hcan1.Init.RFLM = DISABLE;
    hcan1.Init.TXFP = DISABLE;
    if (HAL_CAN_Init(&hcan1) != HAL_OK)
    {
        _Error_Handler(__FILE__, __LINE__);
    }

}

void can_init(void)
{
    rt_hw_can_init();
    struct can_configure cfg;
    cfg.baud_rate = CAN1MBaud;
    cfg.msgboxsz = RT_CANMSG_BOX_SZ;
    cfg.sndboxnumber = RT_CANSND_BOX_NUM;
    cfg.mode = NORMAL;
    cfg.privmode = 0;
    //cfg.maxhdr = 4;
    dev_can1.ops->configure(&dev_can1, &cfg);
    dev_can1.ops->control(&dev_can1, RT_DEVICE_CTRL_SET_INT, (void *)RT_DEVICE_FLAG_INT_RX);
}

char str[10] = {0xFF,0xAA,0x69,0x88,0xB5,0xFF,0xAA,0x76,0x00,0x00}; //Z轴归0
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
	struct rx_msg msg;
    rt_err_t result;
    msg.dev = dev;
    msg.size = size;

    result = rt_mq_send(&uart_mq, &msg, sizeof(msg));
    return result;
}

void uart_init(void)
{
	char uart_rx[44];
	float zeta=180.0;
	serial = rt_device_find(AXIS_UART);
	rt_device_open(serial, RT_DEVICE_FLAG_DMA_RX);
	rt_device_set_rx_indicate(serial, uart_input);
	struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT; 
	config.baud_rate = BAUD_RATE_921600;
	config.data_bits = DATA_BITS_8;
	config.stop_bits = STOP_BITS_1;
	config.parity = PARITY_NONE;
	config.bit_order = BIT_ORDER_LSB;
	config.invert = NRZ_NORMAL;
	config.bufsz = 44;
	config.reserved = 0;	
	rt_device_control(serial, RT_DEVICE_CTRL_CONFIG, &config);
	rt_thread_mdelay(200);
	do//Z轴置零有问题，这样保证清零
	{
		rt_device_write(serial,RT_NULL,str,10);
		rt_thread_mdelay(50);
		if(RT_EOK == rt_mq_recv(&rx_mq,uart_rx,44,RT_WAITING_FOREVER))
		{
			for(rt_uint8_t i=0;i<34;i++)
			{
				if(uart_rx[i] == 0x55 && uart_rx[i+1] == 0x53)
				{
					zeta= (short)((uart_rx[i+7]<<8|uart_rx[i+6]))/32768.0*180; 
				}
			}
		}
	}while(zeta > 1E-6 ||zeta < -1E-6);
}
