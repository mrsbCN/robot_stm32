#include "tid_test.h"

#define QUERY			0
#define ADRC_r			1
#define ADRC_h			2
#define ADRC_h0			3
#define ADRC_w0			4
#define ADRC_b0			5
#define ADRC_beta_0		6
#define ADRC_wc			7

static rt_timer_t timer1;
static rt_uint16_t cnt = 1;
rt_int16_t expect = 0;
rt_uint8_t A =2;
static rt_uint16_t period = 0;
static rt_int16_t arr_sin[16] = {0 ,153 ,283 ,370 ,400 ,370 ,283 ,153 ,0 ,-153 ,-283 ,-370 ,-400 ,-370 ,-283 ,-153};
static rt_tick_t arr_period[] = 
{
	625 ,417 ,313 ,250 ,208 ,179 ,156 ,139 ,125 ,114 ,104 ,96 ,89 ,83 ,
78 ,74 ,69 ,66 ,63 ,60 ,57 ,54 ,52 ,50 ,48 ,46 ,45 ,43 ,42 ,40 ,39 ,
38 ,37 ,36 ,35 ,34 ,33 ,32 ,31 ,30 ,30 ,29 ,28 ,26 ,24 ,22 ,21 ,20 ,
18 ,17 ,16 ,16 ,13 ,10 ,9 ,8 ,7 ,6 
};

void tid_test_entry(void *par)
{
    rt_mutex_take(&mission_mu, RT_WAITING_FOREVER);
    rt_uint32_t recved;

    rt_mb_send(&s_tar_mb[0], 2500);
    rt_mb_send(&s_tar_mb[1], -2500);
	rt_thread_mdelay(5000);
	//rt_mb_send(&dis_tar_mb[0], 1000);
    //rt_mb_send(&dis_tar_mb[1], 1000);
	//rt_event_send(&event_dist, EVENT_DIST);
    //if (RT_EOK == rt_event_recv(&event_done, EVENT_DONE_LEFT | EVENT_DONE_RIGHT, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved))
    //{
    //    rt_kprintf("done1:%d,time:%d\n", recved, (rt_tick_get()));
    //}
    stop();

	rt_mutex_release(&mission_mu);
}

void test_init(void)
{
    tid_test = rt_thread_create("tid_test",
                                   tid_test_entry, RT_NULL,
                                   2048 ,
                                   12 , 10);
    if(tid_test != RT_NULL)
        rt_thread_startup(tid_test);
}

static void change_adrc(int argc, char *argv[])
{
	rt_int32_t cmd1,cmd2;
	cmd1 = atoi(argv[1]);
	cmd2 = atoi(argv[2]);
	rt_kprintf("argc:%d\n",argc);
	rt_kprintf("cmd1:%d,cmd2:%d\n",cmd1,cmd2);
	if(argc ==3)
	{
		switch (cmd1)
		{
			case(ADRC_r)://1
				for(rt_uint8_t i=0;i<2;i++)
				{
					ADRC_SPEED[i].r =cmd2;
				}
				break;
			case(ADRC_h)://2
				for(rt_uint8_t i=0;i<2;i++)
				{
					ADRC_SPEED[i].h =cmd2/1000.0;
				}
				break;
			case(ADRC_h0)://3
				for(rt_uint8_t i=0;i<2;i++)
				{
					ADRC_SPEED[i].h0 =cmd2/1000.0;
				}
				break;
			case(ADRC_w0)://4
				for(rt_uint8_t i=0;i<2;i++)
				{
					ADRC_SPEED[i].beta_01 =3*cmd2;
					ADRC_SPEED[i].beta_02 =3*cmd2*cmd2;
					ADRC_SPEED[i].beta_03 =cmd2*cmd2*cmd2;
				}
				break;
			case(ADRC_b0)://5
				for(rt_uint8_t i=0;i<2;i++)
				{
					ADRC_SPEED[i].b0 =cmd2;
				}
				break;
			case(ADRC_beta_0)://6
				for(rt_uint8_t i=0;i<2;i++)
				{
					ADRC_SPEED[i].beta_0 =cmd2/1000.0;
				}
				break;					
			case(ADRC_wc)://7
				for(rt_uint8_t i=0;i<2;i++)
				{
					ADRC_SPEED[i].beta_1 = cmd2*cmd2;
					ADRC_SPEED[i].beta_2 = 2*cmd2;
				}
				break;
			case(QUERY)://0
				rt_kprintf("r:%d,h:%d,h0:%d,beta_01:%d,beta_02:%d,beta_03:%d,b0:%d,beta_0:%d,beta_1:%d,beta_2:%d\n",
							(int)ADRC_SPEED[0].r,(int)(ADRC_SPEED[0].h*1000),(int)(ADRC_SPEED[0].h0*1000),
							(int)ADRC_SPEED[0].beta_01,(int)ADRC_SPEED[0].beta_02,(int)ADRC_SPEED[0].beta_03,(int)ADRC_SPEED[0].b0,
							(int)(ADRC_SPEED[0].beta_0*1000),(int)ADRC_SPEED[0].beta_1,(int)ADRC_SPEED[0].beta_2);
				break;
		}
		if(cmd1 != QUERY)
		{
			rt_thread_mdelay(3000);
			test_init();
		}
	}
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(change_adrc,"change_adrc canshu  daxiao(h,h0,beta_0 is 1000 plus)");


static void timeout1(void *parameter)
{
	expect = 5*arr_sin[cnt%16];
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

void period_test(void)
{
	rt_thread_mdelay(5000);

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

MSH_CMD_EXPORT(period_test,"period test");
