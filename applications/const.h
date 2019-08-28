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

extern const rt_int32_t loc_left2_x;
extern const rt_int32_t loc_left2_y;

extern const rt_int32_t loc_left3_x;
extern const rt_int32_t loc_left3_y;

extern const rt_int32_t loc_left4_x;
extern const rt_int32_t loc_left4_y;

extern const rt_int32_t loc_left5_x;
extern const rt_int32_t loc_left5_y;

extern const rt_int32_t loc_left6_x;
extern const rt_int32_t loc_left6_y;

extern const rt_int32_t loc_left_done_x;
extern const rt_int32_t loc_left_done_y;

extern const rt_int32_t loc_cir_left2_x;
extern const rt_int32_t loc_cir_left2_y;

extern const rt_int32_t loc_cir_left3_x;
extern const rt_int32_t loc_cir_left3_y;

extern const rt_int32_t loc_cir_left4_x;
extern const rt_int32_t loc_cir_left4_y;

extern const rt_int32_t loc_cir_left5_x;
extern const rt_int32_t loc_cir_left5_y;

extern const rt_int32_t loc_cir_left6_x;
extern const rt_int32_t loc_cir_left6_y;

extern const rt_int32_t loc_cir_left7_x;
extern const rt_int32_t loc_cir_left7_y;

extern const rt_int32_t loc_right2_x;
extern const rt_int32_t loc_right2_y;

extern const rt_int32_t loc_right3_x;
extern const rt_int32_t loc_right3_y;

extern const rt_int32_t loc_right4_x;
extern const rt_int32_t loc_right4_y;

extern const rt_int32_t loc_right5_x;
extern const rt_int32_t loc_right5_y;

extern const rt_int32_t loc_right6_x;
extern const rt_int32_t loc_right6_y;

extern const rt_int32_t loc_right_done_x;
extern const rt_int32_t loc_right_done_y;

extern const rt_int32_t loc_cir_right2_x;
extern const rt_int32_t loc_cir_right2_y;

extern const rt_int32_t loc_cir_right3_x;
extern const rt_int32_t loc_cir_right3_y;

extern const rt_int32_t loc_cir_right4_x;
extern const rt_int32_t loc_cir_right4_y;

extern const rt_int32_t loc_cir_right5_x;
extern const rt_int32_t loc_cir_right5_y;

extern const rt_int32_t loc_cir_right6_x;
extern const rt_int32_t loc_cir_right6_y;

extern const rt_int32_t loc_cir_right7_x;
extern const rt_int32_t loc_cir_right7_y;
