void tid_toR_entry(void *par)
{
    
}

void toR_init(void)
{
		tid_toR = rt_thread_create("led1",
									tid_toR_entry, RT_NULL,
									2048 ,
									8 , 10);
		if(tid_toR != RT_NULL)
			rt_thread_startup(tid_toR);
}