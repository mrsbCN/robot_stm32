#include "sdcard.h"
rt_device_t dev;

const rt_uint8_t black[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
void sd_enter(void * par);

void sd_init(void)
{
  dev = rt_device_find("sd0");
	if(dev != RT_NULL)
	{
		if(dfs_mount("sd0","/","elm",0,0) ==0)
		{
			rt_kprintf("sd card mount to / success!\n");
		}
		else
		{
			rt_kprintf("sd card mount to / failed!\n");
		}			
	}
	
	tid_sd = rt_thread_create("sd",
														sd_enter , RT_NULL,
														1024 ,
														29 , 10);
		if(tid_sd != RT_NULL)
			rt_thread_startup(tid_sd);
}

void sd_enter(void * par)
{
	int fd=RT_NULL;
	rt_uint8_t buf[20];
	rt_uint32_t time;
	while(1)
	{
		if(rt_mq_recv(&sdcard_mq,buf,16,RT_WAITING_FOREVER) ==RT_EOK)  //接受到buf顺序有问题
		{
			fd = open("/can.txt", O_APPEND | O_WRONLY | O_CREAT);
				time = rt_tick_get();
				write(fd,&time,4);
				write(fd,buf,16);
				if(rt_mq_recv(&sdcard_mq,buf,4,RT_WAITING_FOREVER) ==RT_EOK)
				{
					write(fd,buf,4);
				}
				write(fd,black,8);
				fsync(fd);
				close(fd);

		}
	}
}

