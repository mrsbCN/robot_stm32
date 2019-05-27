#ifndef __SDCARD
#define __SDCARD
#include "mailbox.h"
#include "dfs_posix.h"
//#include <rthw.h>
//#define LOG_TAG              "can"
//#define LOG_LVL              LOG_LVL_DBG
//#include <ulog.h>

//static struct ulog_backend sdcard;

static rt_thread_t tid_sd = RT_NULL;
#endif

extern void sd_init(void);
