#include "mailbox.h"
#include "dfs_posix.h"

static rt_thread_t tid_sd = RT_NULL;

extern void sd_init(void);
extern void sd_write(const void * buf1,const void * buf2,const void * buf3);
