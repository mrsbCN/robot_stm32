#include "step.h"

//1,2号参数对应原始左右轮，
void forward(rt_int32_t x, rt_int32_t y)
{
	rt_mb_send(&s_tar_mb[0], spd_for_left);
    rt_mb_send(&s_tar_mb[1], spd_for_right);
    rt_mb_send(&dis_tar_mb[0], x);
    rt_mb_send(&dis_tar_mb[1], y);
    rt_event_send(&event_loca, EVENT_DIST_FOR);
	rt_event_send(&event_loca, EVENT_FOR);
}

void backward(rt_int32_t x, rt_int32_t y)
{
	rt_mb_send(&s_tar_mb[0], spd_back_left);
    rt_mb_send(&s_tar_mb[1], spd_back_right);
    rt_mb_send(&dis_tar_mb[0], x);
    rt_mb_send(&dis_tar_mb[1], y);
    rt_event_send(&event_loca, EVENT_DIST_BACK);
	rt_event_send(&event_loca, EVENT_BACK);
}

void for_turnleft(rt_int32_t x, rt_int32_t y)
{
	rt_mb_send(&s_tar_mb[0], spd_for_tlf_left);
    rt_mb_send(&s_tar_mb[1], spd_for_tlf_right);
    rt_mb_send(&dis_tar_mb[0], x);
    rt_event_send(&event_loca, EVENT_DIST_TURN);
	rt_event_send(&event_loca, EVENT_TURN);
}

void for_turnright(rt_int32_t x, rt_int32_t y)
{
	rt_mb_send(&s_tar_mb[0], spd_for_tri_left);
    rt_mb_send(&s_tar_mb[1], spd_for_tri_right);
    rt_mb_send(&dis_tar_mb[0], x);
    rt_event_send(&event_loca, EVENT_DIST_TURN);
	rt_event_send(&event_loca, EVENT_TURN);
}

void back_turnleft(rt_int32_t x, rt_int32_t y)
{

}

void back_turnright(rt_int32_t x, rt_int32_t y)
{

}

void big_turnleft(rt_int32_t x, rt_int32_t y)
{

}

void big_turnright(rt_int32_t x, rt_int32_t y)
{

}


void turnleft(rt_int32_t x, rt_int32_t y)
{
    rt_mb_send(&s_tar_mb[0], spd_tlf_left);
    rt_mb_send(&s_tar_mb[1], spd_tlf_right);
    rt_mb_send(&dis_tar_mb[0], x);
    rt_event_send(&event_loca, EVENT_DIST_TURN);
	rt_event_send(&event_loca, EVENT_TURN);
}

void turnright(rt_int32_t x, rt_int32_t y)  //输入x为角度*100倍，y不用
{
	rt_mb_send(&s_tar_mb[0], spd_tri_left);
    rt_mb_send(&s_tar_mb[1], spd_tri_right);
    rt_mb_send(&dis_tar_mb[0], x);
    rt_event_send(&event_loca, EVENT_DIST_TURN);
	rt_event_send(&event_loca, EVENT_TURN);
}

void stop(void)
{
	rt_mb_send(&s_tar_mb[0], 0);
    rt_mb_send(&s_tar_mb[1], 0);
}
