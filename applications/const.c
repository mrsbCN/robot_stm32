#include "const.h"

//左转右转速度和路程均以车前进为方向而言。车的左右 变而轮子的左右对应编号0，1不变
const rt_int32_t speed1 = 4320;  	//直行速度

const rt_int32_t spd_for_left = speed1;
const rt_int32_t spd_for_right = -speed1; //前进

const rt_int32_t spd_back_left = -speed1;
const rt_int32_t spd_back_right = speed1;//后退

const rt_int32_t spd_tlf_left = -1000;	
const rt_int32_t spd_tlf_right = -1000;//左转

const rt_int32_t spd_tri_left = 1000;
const rt_int32_t spd_tri_right = 1000;//右转


//上面是速度，下面是坐标点
const rt_int32_t loc_begin_x = 3000;
const rt_int32_t loc_begin_y = 600;

const rt_int32_t loc_R_x = 3000;
const rt_int32_t loc_R_y = 1400;

const rt_int32_t loc_Q_x = 1750;
const rt_int32_t loc_Q_y = 1400;

const rt_int32_t loc_M_x = 1750;
const rt_int32_t loc_M_y = 3250;

const rt_int32_t loc_S_x = 4370;
const rt_int32_t loc_S_y = 1400;

const rt_int32_t loc_N_x = 4370;
const rt_int32_t loc_N_y = 3250;

const rt_int32_t loc_nurse_x = 4330;
const rt_int32_t loc_nurse_y = 1250;

const rt_int32_t loc_nurse2_x = 4310;
const rt_int32_t loc_nurse2_y = 1000;

const rt_int32_t loc_half_be_x = 3250;
const rt_int32_t loc_half_be_y = 750;
