#include "mailbox.h"


//struct rt_messagequeue lf_s_cur_mq,ri_s_cur_mq;
struct rt_ringbuffer s_cur_rb[2];

struct rt_mailbox	s_tar_mb[2], ele_mb[2], total_mb[2], dis_tar_mb[2];
struct rt_event event_per, event_done, event_dist,event_pwm;

struct rt_messagequeue sdcard_mq;
struct rt_mutex  mission_mu;
static rt_uint8_t sdcard[80];

static rt_uint8_t lf_s_cur[12] = {0};
static rt_uint8_t ri_s_cur[12] = {0}; //从CAN总线接收回来的信息

static rt_uint8_t lf_s_tar[4] = {0};
static rt_uint8_t ri_s_tar[4] = {0};		//目标速度+循迹矫正

static rt_uint8_t lf_ele[4] = {0};
static rt_uint8_t ri_ele[4] = {0};		//要发送的电流

static rt_uint8_t total_left[4] = {0};	//总的角度
static rt_uint8_t total_right[4] = {0};

static rt_uint8_t dis_tar_left[4] = {0};	//距离
static rt_uint8_t dis_tar_right[4] = {0};


int msgq_init(void)
{

    rt_ringbuffer_init(&s_cur_rb[0], lf_s_cur, 8);
    rt_ringbuffer_init(&s_cur_rb[1], ri_s_cur, 8);

    rt_mb_init(&s_tar_mb[0], "lf_tar", &lf_s_tar[0], 1, RT_IPC_FLAG_FIFO);
    rt_mb_init(&s_tar_mb[1], "lf_tar", &ri_s_tar[0], 1, RT_IPC_FLAG_FIFO);

    rt_mb_init(&ele_mb[0], "lf_ele", &lf_ele[0], 1, RT_IPC_FLAG_FIFO);
    rt_mb_init(&ele_mb[1], "ri_ele", &ri_ele[0], 1, RT_IPC_FLAG_FIFO);

    rt_mb_init(&total_mb[0], "ang_left", &total_left[0], 1, RT_IPC_FLAG_FIFO);
    rt_mb_init(&total_mb[1], "ang_right", &total_right[0], 1, RT_IPC_FLAG_FIFO);

    rt_mb_init(&dis_tar_mb[0], "dis_left", &dis_tar_left[0], 1, RT_IPC_FLAG_FIFO);
    rt_mb_init(&dis_tar_mb[1], "dis_right", &dis_tar_right[0], 1, RT_IPC_FLAG_FIFO);

    rt_event_init(&event_per, "event_per", RT_IPC_FLAG_FIFO);
    rt_event_init(&event_dist, "event_dist", RT_IPC_FLAG_FIFO);
    rt_event_init(&event_done, "event_done", RT_IPC_FLAG_FIFO);
    rt_event_init(&event_pwm, "event_pwm", RT_IPC_FLAG_FIFO);

    rt_mutex_init(&mission_mu, "mis_mu", RT_IPC_FLAG_FIFO);

    rt_mq_init(&sdcard_mq, "sdcard", &sdcard, 20, 80, RT_IPC_FLAG_FIFO);

    return 0;
}
