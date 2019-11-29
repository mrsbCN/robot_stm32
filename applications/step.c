#include "step.h"

//1,2号参数对应原始左右轮，
void forward(rt_int32_t x, rt_int32_t y,rt_int32_t nl, rt_int32_t nr)
{
	rt_mb_send(&s_tar_mb[0], spd_for_left);
    rt_mb_send(&s_tar_mb[1], spd_for_right);
    rt_mb_send(&dis_tar_mb[0], x);
    rt_mb_send(&dis_tar_mb[1], y);
	rt_mb_send(&s_nx_mb[0],nl);
	rt_mb_send(&s_nx_mb[1],nr);
	
    rt_event_send(&event_loca, EVENT_DIST_FOR);
	rt_event_send(&event_dir, EVENT_FOR);
}

void backward(rt_int32_t x, rt_int32_t y,rt_int32_t nl, rt_int32_t nr)
{
	rt_mb_send(&s_tar_mb[0], spd_back_left);
    rt_mb_send(&s_tar_mb[1], spd_back_right);
    rt_mb_send(&dis_tar_mb[0], x);
    rt_mb_send(&dis_tar_mb[1], y);
	rt_mb_send(&s_nx_mb[0],nl);
	rt_mb_send(&s_nx_mb[1],nr);
	
    rt_event_send(&event_loca, EVENT_DIST_BACK);
	rt_event_send(&event_dir, EVENT_BACK);
}

void turnleft(rt_int32_t x, rt_int32_t y,rt_int32_t nl, rt_int32_t nr)
{
    rt_mb_send(&s_tar_mb[0], spd_tlf_left);
    rt_mb_send(&s_tar_mb[1], spd_tlf_right);
    rt_mb_send(&dis_tar_mb[0], x);
	rt_mb_send(&s_nx_mb[0],nl);
	rt_mb_send(&s_nx_mb[1],nr);
	
    rt_event_send(&event_loca, EVENT_DIST_TURN);
	rt_event_send(&event_dir, EVENT_TURN);
}

void turnright(rt_int32_t x, rt_int32_t y,rt_int32_t nl, rt_int32_t nr)  //输入x为目标角度（不是变化角），y不用
{
	rt_mb_send(&s_tar_mb[0], spd_tri_left);
    rt_mb_send(&s_tar_mb[1], spd_tri_right);
    rt_mb_send(&dis_tar_mb[0], x);
	rt_mb_send(&s_nx_mb[0],nl);
	rt_mb_send(&s_nx_mb[1],nr);
	
    rt_event_send(&event_loca, EVENT_DIST_TURN);
	rt_event_send(&event_dir, EVENT_TURN);
}

void stop(void)
{
	rt_mb_send(&s_tar_mb[0], 0);
    rt_mb_send(&s_tar_mb[1], 0);
	rt_mb_send(&s_nx_mb[0],0);
	rt_mb_send(&s_nx_mb[1],0);
	rt_event_send(&event_dir, EVENT_TURN);
}

void stop_to_for(void)
{
	rt_mb_send(&s_tar_mb[0], 0);
    rt_mb_send(&s_tar_mb[1], 0);
	rt_mb_send(&s_nx_mb[0],0);
	rt_mb_send(&s_nx_mb[1],0);
	rt_event_send(&event_dir, EVENT_FOR);
}

void stop_to_back(void)
{
	rt_mb_send(&s_tar_mb[0], 0);
    rt_mb_send(&s_tar_mb[1], 0);
	rt_mb_send(&s_nx_mb[0],0);
	rt_mb_send(&s_nx_mb[1],0);
	rt_event_send(&event_dir, EVENT_BACK);
}
