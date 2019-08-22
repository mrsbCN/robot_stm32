#include "const.h"

//左转右转速度和路程均以车前进为方向而言。车的左右 变而轮子的左右对应编号0，1不变
const rt_int32_t speed1 = 3000;  	//直行速度

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
const rt_int32_t loc_begin_y = 500;

const rt_int32_t loc_left2_x = 2505;
const rt_int32_t loc_left2_y = 994;

const rt_int32_t loc_left3_x = 2055;
const rt_int32_t loc_left3_y = 1531;

const rt_int32_t loc_left4_x = 1705;
const rt_int32_t loc_left4_y = 2137;

const rt_int32_t loc_left5_x = 1465;
const rt_int32_t loc_left5_y = 2795;

const rt_int32_t loc_left6_x = 1250;
const rt_int32_t loc_left6_y = 4018;

const rt_int32_t loc_left_done_x = 1250;
const rt_int32_t loc_left_done_y = 5100;

const rt_int32_t loc_cir_left2_x = 1386;
const rt_int32_t loc_cir_left2_y = 4724;

const rt_int32_t loc_cir_left3_x = 1586;
const rt_int32_t loc_cir_left3_y = 4377;

const rt_int32_t loc_cir_left4_x = 1843;
const rt_int32_t loc_cir_left4_y = 4071;

const rt_int32_t loc_cir_left5_x = 2150;
const rt_int32_t loc_cir_left5_y = 3814;

const rt_int32_t loc_cir_left6_x = 2496;
const rt_int32_t loc_cir_left6_y = 3614;

const rt_int32_t loc_cir_left7_x = 2872;
const rt_int32_t loc_cir_left7_y = 3477;

const rt_int32_t loc_right2_x = 3494;
const rt_int32_t loc_right2_y = 994;

const rt_int32_t loc_right3_x = 3944;
const rt_int32_t loc_right3_y = 1531;

const rt_int32_t loc_right4_x = 4294;
const rt_int32_t loc_right4_y = 2137;

const rt_int32_t loc_right5_x = 4534;
const rt_int32_t loc_right5_y = 2795;

const rt_int32_t loc_right6_x = 4750;
const rt_int32_t loc_right6_y = 4018;

const rt_int32_t loc_right_done_x = 4750;
const rt_int32_t loc_right_done_y = 5100;

const rt_int32_t loc_cir_right2_x = 4613;
const rt_int32_t loc_cir_right2_y = 4724;

const rt_int32_t loc_cir_right3_x = 4413;
const rt_int32_t loc_cir_right3_y = 4377;

const rt_int32_t loc_cir_right4_x = 4156;
const rt_int32_t loc_cir_right4_y = 4071;

const rt_int32_t loc_cir_right5_x = 3849;
const rt_int32_t loc_cir_right5_y = 3814;

const rt_int32_t loc_cir_right6_x = 3503;
const rt_int32_t loc_cir_right6_y = 3614;

const rt_int32_t loc_cir_right7_x = 3127;
const rt_int32_t loc_cir_right7_y = 3477;