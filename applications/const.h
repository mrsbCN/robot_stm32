#include "rtthread.h"
#define K   0.001278317      //(3.1415*125/8192/36)     //总角度-->距离(mm)系数 pi，轮子直径，一圈信号数，减速比


extern const rt_int32_t speed1 ;  	//直行速度

extern const rt_int32_t spd_for_left;
extern const rt_int32_t spd_for_right;

extern const rt_int32_t spd_back_left;
extern const rt_int32_t spd_back_right;

extern const rt_int32_t spd_tlf_left;	
extern const rt_int32_t spd_tlf_right;

extern const rt_int32_t spd_tri_left;
extern const rt_int32_t spd_tri_right;

//坐标
extern const rt_int32_t loc_begin_x;
extern const rt_int32_t loc_begin_y;

extern const rt_int32_t loc_R_x;
extern const rt_int32_t loc_R_y;

extern const rt_int32_t loc_Q_x;
extern const rt_int32_t loc_Q_y;

extern const rt_int32_t loc_M_x;
extern const rt_int32_t loc_M_y;

extern const rt_int32_t loc_S_x;
extern const rt_int32_t loc_S_y;

extern const rt_int32_t loc_N_x;
extern const rt_int32_t loc_N_y;

extern const rt_int32_t loc_nurse_x;
extern const rt_int32_t loc_nurse_y;

extern const rt_int32_t loc_nurse2_x;
extern const rt_int32_t loc_nurse2_y;

extern const rt_int32_t loc_half_be_x;
extern const rt_int32_t loc_half_be_y;
