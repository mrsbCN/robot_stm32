#include "led.h"
//存放各类GPIO初始化


uint8_t Read_KEY(void) { return rt_pin_read(KEY1_PIN);}

void Btnpwm_Dowm_CallBack(void *btn)		//单击开始运行
{
	rt_pin_write(OPENMV_PIN,PIN_LOW);
	rt_thread_mdelay(10000);
	rt_pin_write(OPENMV_PIN,PIN_HIGH);
	rt_thread_mdelay(50);
	rt_pin_write(OPENMV_PIN,PIN_LOW);
}


void openmv_entry(void *par)
{
	Button_t Button_pwm;
	Button_Create("Button_pwm",
             &Button_pwm, 
             Read_KEY, 
             PIN_HIGH);
	Button_Attach(&Button_pwm,BUTTON_DOWM,Btnpwm_Dowm_CallBack); 
    while (1)
    {
		Button_Process();
        rt_thread_mdelay(50);
    }
}


void led1_entry(void *par)
{
	Button_t Button_pwm;
	Button_Create("Button_pwm",
             &Button_pwm, 
             Read_KEY, 
             PIN_HIGH);
	Button_Attach(&Button_pwm,BUTTON_DOWM,Btnpwm_Dowm_CallBack); 
    while (1)
    {
		Button_Process();
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}

void led2_entry(void *par)
{
	struct rx_msg msg;
	static char rx_temp_p[RT_SERIAL_RB_BUFSZ+1];
	rt_err_t result;
	rt_uint16_t rx_length=0;
    while (1)
    {
		rt_memset(&msg,0,sizeof(msg));
		result = rt_mq_recv(&uart_mq,&msg,sizeof(msg),RT_WAITING_FOREVER);
		if(result == RT_EOK)
		{
			rx_length = 0;
			rx_length = rt_device_read(msg.dev,0,rx_temp_p,msg.size);
			msg.size = rx_length;
			if(rx_length >0)
			{
				rt_mq_send(&rx_mq,&rx_temp_p,rx_length);
			}
		}
    }
}

void led_init(void)
{
    rt_pin_mode(POWER1_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(POWER2_PIN, PIN_MODE_OUTPUT);
	rt_pin_mode(POWERCI_PIN, PIN_MODE_OUTPUT);
	rt_pin_mode(POWER3_PIN, PIN_MODE_OUTPUT);
	rt_pin_mode(SPEAKER1_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(SPEAKER2_PIN, PIN_MODE_OUTPUT);
	rt_pin_mode(SPEAKER3_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(SPEAKER4_PIN, PIN_MODE_OUTPUT);
	rt_pin_mode(OPENMV_PIN, PIN_MODE_OUTPUT);
    
	rt_pin_write(POWER1_PIN, PIN_HIGH);
    rt_pin_write(POWER2_PIN, PIN_HIGH);
	rt_pin_write(POWERCI_PIN, PIN_HIGH);
	rt_pin_write(POWER3_PIN, PIN_HIGH);
	rt_pin_write(SPEAKER1_PIN, PIN_HIGH);
    rt_pin_write(SPEAKER2_PIN, PIN_HIGH);
	rt_pin_write(SPEAKER3_PIN, PIN_HIGH);
    rt_pin_write(SPEAKER4_PIN, PIN_HIGH);
	rt_pin_write(OPENMV_PIN, PIN_HIGH);
	
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);//CAN正常闪烁
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);//程序正常闪烁
	rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);//亮表示先去A
	rt_pin_mode(KEY1_PIN, PIN_MODE_INPUT_PULLDOWN);
	rt_pin_mode(KEY_patient, PIN_MODE_INPUT_PULLDOWN);
	
	rt_pin_write(LED2_PIN, PIN_LOW);
	
    tid_led1 = rt_thread_create("led1",
                                led1_entry , RT_NULL,
                                THREAD_STACK_SIZE ,
                                THREAD_PRIORITY , THREAD_TIMESLICE);
    if(tid_led1 != RT_NULL)
        rt_thread_startup(tid_led1);
	
	tid_led2 = rt_thread_create("uart_rx",
                                led2_entry , RT_NULL,
                                1024 ,
                                24 , 10);
    if(tid_led2 != RT_NULL)
        rt_thread_startup(tid_led2);
	
	tid_led3 = rt_thread_create("openmv",
                                openmv_entry , RT_NULL,
                                THREAD_STACK_SIZE ,
                                THREAD_PRIORITY , THREAD_TIMESLICE);
    if(tid_led3 != RT_NULL)
        rt_thread_startup(tid_led3);
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
	rt_tick_t tim = rt_tick_get();
	while((go_patient == 1) && (rt_tick_get() - tim) < 5000)                            
	{
		Button_Process();
		rt_thread_mdelay(20);
	}
	Button_Delete(&But_patient);
}
