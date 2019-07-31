#include "const.h"

//左转右转速度和路程均以车前进为方向而言。车的左右 变而轮子的左右对应编号0，1不变
const rt_int32_t speed1 = 1000;  	//直行速度
const rt_int32_t speed2 = 750;		//转弯内圈速度
const rt_int32_t speed3 = 1500;		//转弯外圈速度

const rt_int32_t spd_for_left = speed1;
const rt_int32_t spd_for_right = -speed1; //前进

const rt_int32_t spd_back_left = -speed1;
const rt_int32_t spd_back_right = speed1;//后退

const rt_int32_t spd_for_tlf_left = speed2;
const rt_int32_t spd_for_tlf_right = -speed3;//前进左转	

const rt_int32_t spd_for_tri_left = speed3;
const rt_int32_t spd_for_tri_right = -speed2;//前进右转	

const rt_int32_t spd_back_tlf_left = -speed3;
const rt_int32_t spd_back_tlf_right = speed2;//后退左转	

const rt_int32_t spd_back_tri_left = -speed2;
const rt_int32_t spd_back_tri_right = speed3;//后退右转	

const rt_int32_t spd_tlf_left = -speed1;	
const rt_int32_t spd_tlf_right = -speed1;//左转

const rt_int32_t spd_tri_left = speed1;
const rt_int32_t spd_tri_right = speed1;//右转

const rt_int32_t spd_big_tlf_left = -1350;	
const rt_int32_t spd_big_tlf_right = 1050;//大圆左转

const rt_int32_t spd_big_tri_left = -1050;
const rt_int32_t spd_big_tri_right = 1350;//大圆右转


//上面是速度，下面是路程
const rt_int32_t dis_tlf_left = 78;
const rt_int32_t dis_tlf_right = dis_tlf_left;

const rt_int32_t dis_tri_left = dis_tlf_left;
const rt_int32_t dis_tri_right = dis_tlf_left; //以上四个是轮静止，以中心为半径(r=100)的转弯45°的距离


const rt_int32_t dis_for_tlf_left45 = 550;
const rt_int32_t dis_for_tlf_right45 = 707;

const rt_int32_t dis_for_tri_left45 = dis_for_tlf_right45;
const rt_int32_t dis_for_tri_right45 = dis_for_tlf_left45; //以上是运动时，以体外为半径（r=800）的转弯45°的距离

const rt_int32_t dis_for_tlf_left = 5884;
const rt_int32_t dis_for_tlf_right = 5256;

const rt_int32_t dis_for_tri_left = dis_for_tlf_right;
const rt_int32_t dis_for_tri_right = dis_for_tlf_left;

const rt_int32_t dis_back_tlf_left = dis_for_tlf_right;
const rt_int32_t dis_back_tlf_right = dis_for_tlf_left;

const rt_int32_t dis_back_tri_left = dis_for_tlf_left;
const rt_int32_t dis_back_tri_right = dis_for_tlf_right;//以上是运动时，以体外为半径的转弯180°的距离 //暂时是直接转180° 方案，如下

const rt_int32_t dis_big_tlf_left = 5884;
const rt_int32_t dis_big_tlf_right = 5256;

const rt_int32_t dis_big_tri_left = dis_for_tlf_right;
const rt_int32_t dis_big_tri_right = dis_for_tlf_left;

const rt_int32_t be_to_left1 = 2173;
const rt_int32_t left1_to_left3 = 2320;
const rt_int32_t left3_to_left2 = 1400;//暂时不用

const rt_int32_t left2_to_right2 = 1400;//暂时不用
const rt_int32_t right2_to_right3 = 1960;//暂时不用

const rt_int32_t right3_to_right1 = 2320;
const rt_int32_t right1_to_be = 2173;

//先去右边
const rt_int32_t be_to_right1 = 2173;
const rt_int32_t right1_to_right3 = 2320;
const rt_int32_t right3_to_right2 = 1400;//暂时不用

const rt_int32_t right2_to_left2 = 1400;//暂时不用
const rt_int32_t left2_to_left3 = 1960;//暂时不用

const rt_int32_t left3_to_left1 = 2320;
const rt_int32_t left1_to_be = 2173;
