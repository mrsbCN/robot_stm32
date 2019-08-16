#include "mailbox.h"


struct rt_ringbuffer s_cur_rb[2];

struct rt_mailbox	s_tar_mb[2], dis_tar_mb[2],loc_now_mb[2],s_kf_mb[2],s_error,angle_to_use;
struct rt_event event_per, event_done, event_loca,event_pwm,event_patient,event_test;
struct rt_semaphore uart_rx_sem;

struct rt_messagequeue sdcard_mq;
struct rt_mutex  mission_mu;
static rt_uint8_t sdcard[80];

static rt_uint8_t lf_s_cur[12] = {0};
static rt_uint8_t ri_s_cur[12] = {0}; 		//从CAN总线接收回来的信息 (好像需要多几个字节放指针）

static rt_uint8_t lf_s_tar[4] = {0};
static rt_uint8_t ri_s_tar[4] = {0};		//目标速度+循迹矫正


static rt_uint8_t dis_tar_left[4] = {0};	//距离
static rt_uint8_t dis_tar_right[4] = {0};

static rt_uint8_t loc_now_x[4] = {0};	//当前x,y位置
static rt_uint8_t loc_now_y[4] = {0};

static rt_uint8_t s_kf_lf[4] = {0};
static rt_uint8_t s_kf_ri[4] = {0};
static rt_uint8_t s_error_[4] = {0};
static rt_uint8_t angle_to_use_[4] = {0};

int msgq_init(void)
{

    rt_ringbuffer_init(&s_cur_rb[0], lf_s_cur, 8);
    rt_ringbuffer_init(&s_cur_rb[1], ri_s_cur, 8);

    rt_mb_init(&s_tar_mb[0], "lf_tar", &lf_s_tar[0], 1, RT_IPC_FLAG_FIFO);
    rt_mb_init(&s_tar_mb[1], "ri_tar", &ri_s_tar[0], 1, RT_IPC_FLAG_FIFO);

    rt_mb_init(&dis_tar_mb[0], "dis_left", &dis_tar_left[0], 1, RT_IPC_FLAG_FIFO);
    rt_mb_init(&dis_tar_mb[1], "dis_right", &dis_tar_right[0], 1, RT_IPC_FLAG_FIFO);
	rt_mb_init(&s_kf_mb[0], "s_kf_lf", &s_kf_lf[0], 1, RT_IPC_FLAG_FIFO);
	rt_mb_init(&s_kf_mb[1], "s_kf_lf", &s_kf_ri[0], 1, RT_IPC_FLAG_FIFO);
	rt_mb_init(&s_error, "s_error", &s_error_[0], 1, RT_IPC_FLAG_FIFO);
	rt_mb_init(&angle_to_use, "angle_to_use", &angle_to_use_[0], 1, RT_IPC_FLAG_FIFO);
	rt_mb_init(&loc_now_mb[0], "loc_now_x", &loc_now_x[0], 1, RT_IPC_FLAG_FIFO);
    rt_mb_init(&loc_now_mb[1], "loc_now_y", &loc_now_y[0], 1, RT_IPC_FLAG_FIFO);
	
    rt_event_init(&event_per, "event_per", RT_IPC_FLAG_FIFO);
    rt_event_init(&event_loca, "event_dist", RT_IPC_FLAG_FIFO);
    rt_event_init(&event_done, "event_done", RT_IPC_FLAG_FIFO);
    rt_event_init(&event_pwm, "event_pwm", RT_IPC_FLAG_FIFO);
	rt_event_init(&event_test, "event_test", RT_IPC_FLAG_FIFO);
	rt_event_init(&event_patient, "event_patient", RT_IPC_FLAG_FIFO);
	rt_sem_init(&uart_rx_sem, "uart_rx_sem", 0, RT_IPC_FLAG_FIFO);
	
    rt_mutex_init(&mission_mu, "mis_mu", RT_IPC_FLAG_FIFO);


    return 0;
}
