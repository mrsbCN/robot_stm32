#include "step.h"

void forward(rt_int32_t left, rt_int32_t right)
{
    rt_mb_send(&s_tar_mb[0], spd_for_left);
    rt_mb_send(&s_tar_mb[1], spd_for_right);
    rt_mb_send(&dis_tar_mb[0], left);
    rt_mb_send(&dis_tar_mb[1], right);
    rt_event_send(&event_dist, EVENT_DIST);
}

void backward(rt_int32_t left, rt_int32_t right)
{
    rt_mb_send(&s_tar_mb[0], spd_back_left);
    rt_mb_send(&s_tar_mb[1], spd_back_right);
    rt_mb_send(&dis_tar_mb[0], left);
    rt_mb_send(&dis_tar_mb[1], right);
    rt_event_send(&event_dist, EVENT_DIST);
}

void for_turnleft(rt_int32_t left, rt_int32_t right)
{
    rt_mb_send(&s_tar_mb[0], spd_for_tlf_left);
    rt_mb_send(&s_tar_mb[1], spd_for_tlf_right);
    rt_mb_send(&dis_tar_mb[0], left);
    rt_mb_send(&dis_tar_mb[1], right);
    rt_event_send(&event_dist, EVENT_DIST);
}

void for_turnright(rt_int32_t left, rt_int32_t right)
{
    rt_mb_send(&s_tar_mb[0], spd_for_tri_left);
    rt_mb_send(&s_tar_mb[1], spd_for_tri_right);
    rt_mb_send(&dis_tar_mb[0], left);
    rt_mb_send(&dis_tar_mb[1], right);
    rt_event_send(&event_dist, EVENT_DIST);
}

void back_turnleft(rt_int32_t left, rt_int32_t right)
{
    rt_mb_send(&s_tar_mb[0], spd_back_tlf_left);
    rt_mb_send(&s_tar_mb[1], spd_back_tlf_right);
    rt_mb_send(&dis_tar_mb[0], left);
    rt_mb_send(&dis_tar_mb[1], right);
    rt_event_send(&event_dist, EVENT_DIST);
}

void back_turnright(rt_int32_t left, rt_int32_t right)
{
    rt_mb_send(&s_tar_mb[0], spd_back_tri_left);
    rt_mb_send(&s_tar_mb[1], spd_back_tri_right);
    rt_mb_send(&dis_tar_mb[0], left);
    rt_mb_send(&dis_tar_mb[1], right);
    rt_event_send(&event_dist, EVENT_DIST);
}

void stop(void)
{
    rt_mb_send(&s_tar_mb[0], 0);
    rt_mb_send(&s_tar_mb[1], 0);
}
