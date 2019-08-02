#include "tid_test.h"


static rt_timer_t timer1;
static rt_uint16_t cnt = 1;
rt_int16_t expect = 0;
rt_uint8_t A =2;
struct rt_event event_test;
static rt_uint16_t period = 0;
static rt_int16_t arr_sin[16] = {0 ,153 ,283 ,370 ,400 ,370 ,283 ,153 ,0 ,-153 ,-283 ,-370 ,-400 ,-370 ,-283 ,-153};
static rt_tick_t arr_period[] = 
{
	62500 ,41700 ,3130 ,2500 ,2080 ,1790 ,1560 ,1390 ,1250 ,1140 ,1040 ,960 ,890 ,830 ,
78 ,74 ,69 ,66 ,63 ,60 ,57 ,54 ,52 ,50 ,48 ,46 ,45 ,43 ,42 ,40 ,39 ,
38 ,37 ,36 ,35 ,34 ,33 ,32 ,31 ,30 ,30 ,29 ,28 ,26 ,24 ,22 ,21 ,20 ,
18 ,17 ,16 ,16 ,13 ,10 ,9 ,8 ,7 ,6 
};
static void timeout1(void *parameter)
{
	expect = 6*arr_sin[cnt%16];
    rt_mb_send(&s_tar_mb[0], expect);
    rt_mb_send(&s_tar_mb[1], -expect);
		
    /* 运行第 20*16 次，停止周期定时器 */
    if (cnt++>= 320)
    {
		cnt = 0;
        rt_timer_stop(timer1);
		rt_event_send(&event_test,EVENT_TEST);
    }
}

void test_init(void)
{

	/* 创建定时器 1  周期定时器 */
    timer1 = rt_timer_create("mytimer1", timeout1,
                             RT_NULL, arr_period[period],
                             RT_TIMER_FLAG_PERIODIC);

    /* 启动定时器 1 */
    if (timer1 != RT_NULL) 
		rt_timer_start(timer1);
    rt_event_init(&event_test, "event_per", RT_IPC_FLAG_FIFO);
	while(1)
	{
		if(RT_EOK == rt_event_recv(&event_test,EVENT_TEST, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, RT_NULL))
		{
			period +=1;
			rt_timer_control(timer1,RT_TIMER_CTRL_SET_TIME,&arr_period[period]);
			rt_timer_start(timer1);
			rt_kprintf("%d\n",arr_period[period]);
			//if (period % 8 ==0)
			//{
			//	A ++;
			//}
			if (period == 58)
			{
			   rt_mb_send(&s_tar_mb[0], 0);
				rt_mb_send(&s_tar_mb[1], 0);
				break;
			}
		}
	}
}
