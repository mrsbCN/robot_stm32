#include "sdcard.h"
rt_device_t dev;
int fd=RT_NULL;
const rt_uint8_t t[4] = {0x79,0xfe,0xfe,0xfe};
const rt_uint8_t n[4] = {0xed,0x1e,0xff,0xfe};
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
	
	rt_thread_mdelay(10);
}

void sd_write(const void * buf1,const void * buf2,const void * buf3)
{
	fd = open("/can.txt",O_WRONLY | O_APPEND| O_CREAT);
	rt_uint32_t time;
	time = rt_tick_get();
	write(fd,&time,4);
	write(fd,&t,4);
	write(fd,buf1,8);
	write(fd,&t,4);
	write(fd,buf2,8);
	write(fd,&t,4);
	write(fd,buf3,4);
	write(fd,&n,4);
	fsync(fd);
	close(fd);
}
