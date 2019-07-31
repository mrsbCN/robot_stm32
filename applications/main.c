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

CAN_HandleTypeDef hcan1;
SPI_HandleTypeDef hspi5;
rt_uint8_t status = 0x0;
rt_uint8_t go = 0x1;
struct rt_spi_device *spi_dev;
void HAL_UART_MspInit(UART_HandleTypeDef *huart);
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart);
void MX_CAN1_Init(void);
void HAL_CAN_MspInit(CAN_HandleTypeDef *canHandle);
void HAL_CAN_MspDeInit(CAN_HandleTypeDef *canHandle);
void MX_SPI5_Init(void);
void can_init(void);
void spi_init(void);
Button_t Button1;

uint8_t Read_KEY1_Level(void) { return rt_pin_read(KEY1_PIN);}

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
    rt_thread_mdelay(100);
    MX_CAN1_Init();
    //MX_SPI5_Init();
    can_init();
    msgq_init();
    led_init();
    //rt_hw_spi_device_attach("spi5", "mpu6500", GPIOF, GPIO_PIN_6);
    sd_init();
    rt_thread_mdelay(200);
    cal_init();
    dis_init();
 
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
		test_init();

	}
	else if (status == 1)
	{
		rt_kprintf("go B first!\n");
		rt_thread_mdelay(1);
		to_right_init();
		rt_thread_mdelay(1);
		right_to_left_init();
		rt_thread_mdelay(1);
		left_to_be_init();
	}
    rt_mutex_release(&mission_mu);
    return RT_EOK;
}



void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(huart->Instance == USART2)
    {
        /* USER CODE BEGIN USART2_MspInit 0 */

        /* USER CODE END USART2_MspInit 0 */
        /* Peripheral clock enable */
        __HAL_RCC_USART2_CLK_ENABLE();

        __HAL_RCC_GPIOD_CLK_ENABLE();
        /**USART2 GPIO Configuration
        PD6     ------> USART2_RX
        PD5     ------> USART2_TX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_5;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

        /* USER CODE BEGIN USART2_MspInit 1 */

        /* USER CODE END USART2_MspInit 1 */
    }

}


/**
* @brief UART MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{

    if(huart->Instance == USART2)
    {
        /* USER CODE BEGIN USART2_MspDeInit 0 */

        /* USER CODE END USART2_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_USART2_CLK_DISABLE();

        /**USART2 GPIO Configuration
        PD6     ------> USART2_RX
        PD5     ------> USART2_TX
        */
        HAL_GPIO_DeInit(GPIOD, GPIO_PIN_6 | GPIO_PIN_5);

        /* USER CODE BEGIN USART2_MspDeInit 1 */

        /* USER CODE END USART2_MspDeInit 1 */
    }

}

/* CAN1 init function */
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


void HAL_CAN_MspInit(CAN_HandleTypeDef *canHandle)
{

    GPIO_InitTypeDef GPIO_InitStruct;
    if(canHandle->Instance == CAN1)
    {
        /* USER CODE BEGIN CAN1_MspInit 0 */

        /* USER CODE END CAN1_MspInit 0 */
        /* CAN1 clock enable */
        __HAL_RCC_CAN1_CLK_ENABLE();

        /**CAN1 GPIO Configuration
        PD0     ------> CAN1_RX
        PD1     ------> CAN1_TX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

        /* CAN1 interrupt Init */
        HAL_NVIC_SetPriority(CAN1_TX_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
        HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
        /* USER CODE BEGIN CAN1_MspInit 1 */

        /* USER CODE END CAN1_MspInit 1 */
    }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef *canHandle)
{

    if(canHandle->Instance == CAN1)
    {
        /* USER CODE BEGIN CAN1_MspDeInit 0 */

        /* USER CODE END CAN1_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_CAN1_CLK_DISABLE();

        /**CAN1 GPIO Configuration
        PD0     ------> CAN1_RX
        PD1     ------> CAN1_TX
        */
        HAL_GPIO_DeInit(GPIOD, GPIO_PIN_0 | GPIO_PIN_1);

        /* CAN1 interrupt Deinit */
        HAL_NVIC_DisableIRQ(CAN1_TX_IRQn);
        HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
        /* USER CODE BEGIN CAN1_MspDeInit 1 */

        /* USER CODE END CAN1_MspDeInit 1 */
    }
}

/* USER CODE BEGIN 1 */

/**
* @brief SD MSP Initialization
* This function configures the hardware resources used in this example
* @param hsd: SD handle pointer
* @retval None
*/
void HAL_SD_MspInit(SD_HandleTypeDef *hsd)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(hsd->Instance == SDIO)
    {
        /* USER CODE BEGIN SDIO_MspInit 0 */

        /* USER CODE END SDIO_MspInit 0 */
        /* Peripheral clock enable */
        __HAL_RCC_SDIO_CLK_ENABLE();

        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();
        /**SDIO GPIO Configuration
        PC12     ------> SDIO_CK
        PC11     ------> SDIO_D3
        PC10     ------> SDIO_D2
        PD2     ------> SDIO_CMD
        PC9     ------> SDIO_D1
        PC8     ------> SDIO_D0
        */
        GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_11 | GPIO_PIN_10 | GPIO_PIN_9
                              | GPIO_PIN_8;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF12_SDIO;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF12_SDIO;
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

        /* USER CODE BEGIN SDIO_MspInit 1 */

        /* USER CODE END SDIO_MspInit 1 */
    }

}

/**
* @brief SD MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hsd: SD handle pointer
* @retval None
*/
void HAL_SD_MspDeInit(SD_HandleTypeDef *hsd)
{
    if(hsd->Instance == SDIO)
    {
        /* USER CODE BEGIN SDIO_MspDeInit 0 */

        /* USER CODE END SDIO_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_SDIO_CLK_DISABLE();

        /**SDIO GPIO Configuration
        PC12     ------> SDIO_CK
        PC11     ------> SDIO_D3
        PC10     ------> SDIO_D2
        PD2     ------> SDIO_CMD
        PC9     ------> SDIO_D1
        PC8     ------> SDIO_D0
        */
        HAL_GPIO_DeInit(GPIOC, GPIO_PIN_12 | GPIO_PIN_11 | GPIO_PIN_10 | GPIO_PIN_9
                        | GPIO_PIN_8);

        HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);

        /* USER CODE BEGIN SDIO_MspDeInit 1 */

        /* USER CODE END SDIO_MspDeInit 1 */
    }

}


void MX_SPI5_Init(void)
{

    hspi5.Instance = SPI5;
    hspi5.Init.Mode = SPI_MODE_MASTER;
    hspi5.Init.Direction = SPI_DIRECTION_2LINES;
    hspi5.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi5.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi5.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi5.Init.NSS = SPI_NSS_SOFT;
    hspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
    hspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi5.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi5.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi5.Init.CRCPolynomial = 10;
    if (HAL_SPI_Init(&hspi5) != HAL_OK)
    {
        Error_Handler();
    }

}

/**
* @brief SPI MSP Initialization
* This function configures the hardware resources used in this example
* @param hspi: SPI handle pointer
* @retval None
*/
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(hspi->Instance == SPI5)
    {
        /* USER CODE BEGIN SPI5_MspInit 0 */

        /* USER CODE END SPI5_MspInit 0 */
        /* Peripheral clock enable */
        __HAL_RCC_SPI5_CLK_ENABLE();

        __HAL_RCC_GPIOF_CLK_ENABLE();
        /**SPI5 GPIO Configuration
        PF7     ------> SPI5_SCK
        PF9     ------> SPI5_MOSI
        PF8     ------> SPI5_MISO
        */
        GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_9 | GPIO_PIN_8;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI5;
        HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

        /* USER CODE BEGIN SPI5_MspInit 1 */

        /* USER CODE END SPI5_MspInit 1 */
    }

}

/**
* @brief SPI MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hspi: SPI handle pointer
* @retval None
*/
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
    if(hspi->Instance == SPI5)
    {
        /* USER CODE BEGIN SPI5_MspDeInit 0 */

        /* USER CODE END SPI5_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_SPI5_CLK_DISABLE();

        /**SPI5 GPIO Configuration
        PF7     ------> SPI5_SCK
        PF9     ------> SPI5_MOSI
        PF8     ------> SPI5_MISO
        */
        HAL_GPIO_DeInit(GPIOF, GPIO_PIN_7 | GPIO_PIN_9 | GPIO_PIN_8);

        /* USER CODE BEGIN SPI5_MspDeInit 1 */

        /* USER CODE END SPI5_MspDeInit 1 */
    }

}


void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
  if(htim_base->Instance==TIM8)
  {
  /* USER CODE BEGIN TIM8_MspInit 0 */

  /* USER CODE END TIM8_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM8_CLK_ENABLE();
  /* USER CODE BEGIN TIM8_MspInit 1 */

  /* USER CODE END TIM8_MspInit 1 */
  }

}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(htim->Instance==TIM8)
  {
  /* USER CODE BEGIN TIM8_MspPostInit 0 */

  /* USER CODE END TIM8_MspPostInit 0 */
  
    __HAL_RCC_GPIOI_CLK_ENABLE();
    /**TIM8 GPIO Configuration    
    PI6     ------> TIM8_CH2
    PI5     ------> TIM8_CH1 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF3_TIM8;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM8_MspPostInit 1 */

  /* USER CODE END TIM8_MspPostInit 1 */
  }

}
/**
* @brief TIM_Base MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param htim_base: TIM_Base handle pointer
* @retval None
*/
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{
  if(htim_base->Instance==TIM8)
  {
  /* USER CODE BEGIN TIM8_MspDeInit 0 */

  /* USER CODE END TIM8_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM8_CLK_DISABLE();
  /* USER CODE BEGIN TIM8_MspDeInit 1 */

  /* USER CODE END TIM8_MspDeInit 1 */
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

