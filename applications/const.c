#include "const.h"

//��ת��ת�ٶȺ�·�̾��Գ�ǰ��Ϊ������ԡ��������� ������ӵ����Ҷ�Ӧ���0��1����
const rt_int32_t speed1 = 1000;  	//ֱ���ٶ�
const rt_int32_t speed2 = 750;		//ת����Ȧ�ٶ�
const rt_int32_t speed3 = 1500;		//ת����Ȧ�ٶ�

const rt_int32_t spd_for_left = -speed1;
const rt_int32_t spd_for_right = speed1; //ǰ��

const rt_int32_t spd_back_left = speed1;
const rt_int32_t spd_back_right = -speed1;//����

const rt_int32_t spd_for_tlf_left = -speed2;
const rt_int32_t spd_for_tlf_right = speed3;//ǰ����ת	

const rt_int32_t spd_for_tri_left = -speed3;
const rt_int32_t spd_for_tri_right = speed2;//ǰ����ת	

const rt_int32_t spd_back_tlf_left = speed3;
const rt_int32_t spd_back_tlf_right = -speed2;//������ת	

const rt_int32_t spd_back_tri_left = speed2;
const rt_int32_t spd_back_tri_right = -speed3;//������ת	

const rt_int32_t spd_tlf_left = -speed1;	
const rt_int32_t spd_tlf_right = speed1;//��ת

const rt_int32_t spd_tri_left = -speed1;
const rt_int32_t spd_tri_right = speed1;//��ת

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

//��ȥ�ұ�
const rt_int32_t be_to_right1 = 710;
const rt_int32_t right1_to_right3 = 710;
const rt_int32_t right3_to_right2 = 1400;

const rt_int32_t right2_to_left2 = 1400;
const rt_int32_t left2_to_left3 = 1960;

const rt_int32_t left3_to_left1 = 1960;
const rt_int32_t left1_to_be = 1400;
