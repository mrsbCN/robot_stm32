#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "drv_can.h"
#include "dji_pid.h"
#include "mailbox.h"

void walk_init(void);



extern struct rt_messagequeue lf_s_cur_mq,ri_s_cur_mq,lf_s_tar_mq,ri_s_tar_mq;
