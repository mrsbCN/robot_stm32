#include "led.h"
//存放各类GPIO初始化

void led1_entry(void *par)
{

    while (1)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}

void led2_entry(void *par)
{

    while (1)
    {
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}

void led_init(void)
{
    rt_pin_mode(POWER1_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(POWER2_PIN, PIN_MODE_OUTPUT);
	rt_pin_mode(SPEAKER1_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(SPEAKER2_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(SPI5_NSS, PIN_MODE_OUTPUT);
    
	rt_pin_write(POWER1_PIN, PIN_HIGH);
    rt_pin_write(POWER2_PIN, PIN_HIGH);
	rt_pin_write(SPEAKER1_PIN, PIN_HIGH);
    rt_pin_write(SPEAKER2_PIN, PIN_HIGH);
    rt_pin_write(SPI5_NSS, PIN_LOW);

    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);//CAN正常闪烁
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);//程序正常闪烁
	rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);//亮表示先去A
    //rt_pin_mode(KEY1_PIN, PIN_MODE_INPUT_PULLDOWN);
	rt_pin_mode(KEY_patient, PIN_MODE_INPUT_PULLDOWN);
	
	rt_pin_write(LED2_PIN, PIN_LOW);
	
    tid_led1 = rt_thread_create("led1",
                                led1_entry , RT_NULL,
                                THREAD_STACK_SIZE ,
                                THREAD_PRIORITY , THREAD_TIMESLICE);
    if(tid_led1 != RT_NULL)
        rt_thread_startup(tid_led1);

}


uint8_t Read_KEY_patient_Level(void) { return rt_pin_read(KEY_patient);}

void Btn_patient_Dowm(void *btn)		//单击开始运行
{
	rt_kprintf("KEY_patient Click!\n");
	rt_event_send(&event_patient,EVENT_PATIENT);
	go_patient = 0;
}

void wait_for_patient(void)
{
	Button_Create("But_patient",
              &But_patient, 
              Read_KEY_patient_Level, 
              PIN_HIGH);
	Button_Attach(&But_patient,BUTTON_DOWM,Btn_patient_Dowm);
	go_patient = 1;
	while(go_patient)                            
	{
		Button_Process();
		rt_thread_mdelay(20);
	}
	Button_Delete(&But_patient);
}
