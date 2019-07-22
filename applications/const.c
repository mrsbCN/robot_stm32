#include "const.h"

//左转右转速度和路程均以车前进为方向而言。车的左右 变而轮子的左右对应编号0，1不变
const rt_int32_t speed1 = 1000;  	//直行速度
const rt_int32_t speed2 = 750;		//转弯内圈速度
const rt_int32_t speed3 = 1500;		//转弯外圈速度

const rt_int32_t spd_for_left = -speed1;
const rt_int32_t spd_for_right = speed1; //前进

const rt_int32_t spd_back_left = speed1;
const rt_int32_t spd_back_right = -speed1;//后退

const rt_int32_t spd_for_tlf_left = -speed2;
const rt_int32_t spd_for_tlf_right = speed3;//前进左转	

const rt_int32_t spd_for_tri_left = -speed3;
const rt_int32_t spd_for_tri_right = speed2;//前进右转	

const rt_int32_t spd_back_tlf_left = speed3;
const rt_int32_t spd_back_tlf_right = -speed2;//后退左转	

const rt_int32_t spd_back_tri_left = speed2;
const rt_int32_t spd_back_tri_right = -speed3;//后退右转	

const rt_int32_t spd_tlf_left = -speed1;	
const rt_int32_t spd_tlf_right = speed1;//左转

const rt_int32_t spd_tri_left = -speed1;
const rt_int32_t spd_tri_right = speed1;//右转

const rt_int32_t dis_tlf_left = 130;
const rt_int32_t dis_tlf_right = 130;

const rt_int32_t dis_tri_left = 130;
const rt_int32_t dis_tri_right = 130;

const rt_int32_t dis_for_tlf_left45 = 130;
const rt_int32_t dis_for_tlf_right45 = 260;

const rt_int32_t dis_for_tri_left45 = dis_for_tlf_right45;
const rt_int32_t dis_for_tri_right45 = dis_for_tlf_left45;

const rt_int32_t dis_for_tlf_left = 260;
const rt_int32_t dis_for_tlf_right = 520;

const rt_int32_t dis_for_tri_left = dis_for_tlf_right;
const rt_int32_t dis_for_tri_right = dis_for_tlf_left;

const rt_int32_t dis_back_tlf_left = dis_for_tlf_right;
const rt_int32_t dis_back_tlf_right = dis_for_tlf_left;

const rt_int32_t dis_back_tri_left = dis_for_tlf_left;
const rt_int32_t dis_back_tri_right = dis_for_tlf_right;

const rt_int32_t be_to_left1 = 710;
const rt_int32_t left1_to_left3 = 710;
const rt_int32_t left3_to_left2 = 1400;

const rt_int32_t left2_to_right2 = 1400;
const rt_int32_t right2_to_right3 = 1960;

const rt_int32_t right3_to_right1 = 1960;
const rt_int32_t right1_to_be = 1400;

//先去右边
const rt_int32_t be_to_right1 = 710;
const rt_int32_t right1_to_right3 = 710;
const rt_int32_t right3_to_right2 = 1400;

const rt_int32_t right2_to_left2 = 1400;
const rt_int32_t left2_to_left3 = 1960;

const rt_int32_t left3_to_left1 = 1960;
const rt_int32_t left1_to_be = 1400;
