#include "sdcard.h"
rt_device_t dev;

const rt_uint8_t black[8] = {0xff, 0xff, 0xff, 0x00, 0xfe, 0xfe, 0xfe, 0xfe};
void sd_enter(void *par);
int fd = RT_NULL;

void sd_init(void)
{
    dev = rt_device_find("sd0");
    if(dev != RT_NULL)
    {
        if(dfs_mount("sd0", "/", "elm", 0, 0) == 0)
        {
            rt_kprintf("sd card mount to / success!\n");
        }
        else
        {
            rt_kprintf("sd card mount to / failed!\n");
        }
    }
    //fd = open("/can.txt", O_APPEND | O_WRONLY | O_CREAT);
    tid_sd = rt_thread_create("sd",
                              sd_enter , RT_NULL,
                              1024 ,
                              29 , 10);
    if(tid_sd != RT_NULL)
        rt_thread_startup(tid_sd);
}

void sd_enter(void *par)
{
    int fd = RT_NULL;
    rt_uint8_t buf[20];
    rt_uint32_t time;
    while(1)
    {
        if(rt_mq_recv(&sdcard_mq, buf, 20, RT_WAITING_FOREVER) == RT_EOK) //接受到buf顺序有问题
        {
            fd = open("/can.txt", O_APPEND | O_WRONLY | O_CREAT);
            time = rt_tick_get();
            write(fd, &time, 4);
            write(fd, buf, 20);
            write(fd, black, 8);
            fsync(fd);
            close(fd);

        }
    }
}


//void ulog_sdcard_backend_output(struct ulog_backend *backend,
//																rt_uint32_t level,
//																const char *tag,
//																rt_bool_t is_raw,
//																const char *log,
//																size_t len)
//{
//
//				write(fd,log,len);
//				fsync(fd);
//				//close(fd);
//}
//
//int ulog_sdcard_backend_init(void)
//{
//    ulog_init();
//    sdcard.output = ulog_sdcard_backend_output;
//
//    ulog_backend_register(&sdcard, "sdcard", RT_TRUE);
//
//    return 0;
//}
//INIT_PREV_EXPORT(ulog_sdcard_backend_init);
