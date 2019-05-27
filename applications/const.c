#include "const.h"

const rt_int32_t speed1 = 1000;  	//直行速度
const rt_int32_t speed2 = 750;		//转弯内圈速度
const rt_int32_t speed3 = 1500;		//转弯外圈速度

const rt_int32_t spd_for_left=-speed1;		
const rt_int32_t spd_for_right=speed1;

const rt_int32_t spd_back_left=speed1;
const rt_int32_t spd_back_right=-speed1;

const rt_int32_t spd_for_tlf_left=-speed2;	//左转右转均以车前进方向，车的左右 变而轮子的左右对应编号0，1不变
const rt_int32_t spd_for_tlf_right=speed3;

const rt_int32_t spd_for_tri_left=-speed3;
const rt_int32_t spd_for_tri_right=speed2;

const rt_int32_t spd_back_tlf_left=speed3;
const rt_int32_t spd_back_tlf_right=-speed2;

const rt_int32_t spd_back_tri_left=speed2;
const rt_int32_t spd_back_tri_right=-speed3;

const rt_int32_t be_to_R=430;

const rt_int32_t dis_for_tlf_left=284;
const rt_int32_t dis_for_tlf_right=568;

const rt_int32_t dis_for_tri_left=dis_for_tlf_right;
const rt_int32_t dis_for_tri_right=dis_for_tlf_left;

const rt_int32_t dis_back_tlf_left=dis_for_tri_left;
const rt_int32_t dis_back_tlf_right=dis_for_tri_right;

const rt_int32_t dis_back_tri_left=dis_for_tlf_left;
const rt_int32_t dis_back_tri_right=dis_for_tlf_right;

const rt_int32_t R_to_Q=600;

const rt_int32_t Q_to_M=1300;

const rt_int32_t M_to_Q=1300;

const rt_int32_t Q_to_S=1200;

const rt_int32_t S_to_N=1300;

const rt_int32_t N_to_S=1300;

const rt_int32_t S_to_R=600;

const rt_int32_t halfR_to_be=300;
