#include "const.h"

//��ת��ת�ٶȺ�·�̾��Գ�ǰ��Ϊ������ԡ��������� ������ӵ����Ҷ�Ӧ���0��1����
const rt_int32_t speed1 = 5000;  	//ֱ���ٶ�
const rt_int32_t speed2 = 4750;		//ת����Ȧ�ٶ�
const rt_int32_t speed3 = 5250;		//ת����Ȧ�ٶ�

const rt_int32_t spd_for_left = speed1;
const rt_int32_t spd_for_right = -speed1; //ǰ��

const rt_int32_t spd_back_left = -speed1;
const rt_int32_t spd_back_right = speed1;//����

const rt_int32_t spd_for_tlf_left = speed2;
const rt_int32_t spd_for_tlf_right = -speed3;//ǰ����ת	

const rt_int32_t spd_for_tri_left = speed3;
const rt_int32_t spd_for_tri_right = -speed2;//ǰ����ת	

const rt_int32_t spd_back_tlf_left = -speed3;
const rt_int32_t spd_back_tlf_right = speed2;//������ת	

const rt_int32_t spd_back_tri_left = -speed2;
const rt_int32_t spd_back_tri_right = speed3;//������ת	

const rt_int32_t spd_tlf_left = -1000;	
const rt_int32_t spd_tlf_right = -1000;//��ת

const rt_int32_t spd_tri_left = 1000;
const rt_int32_t spd_tri_right = 1000;//��ת

const rt_int32_t spd_big_tlf_left = -5550;	
const rt_int32_t spd_big_tlf_right = 4950;//��Բ��ת

const rt_int32_t spd_big_tri_left = -4950;
const rt_int32_t spd_big_tri_right = 5550;//��Բ��ת


//�������ٶȣ�������·��
const rt_int32_t dis_tlf_left = 78;
const rt_int32_t dis_tlf_right = dis_tlf_left;

const rt_int32_t dis_tri_left = dis_tlf_left;
const rt_int32_t dis_tri_right = dis_tlf_left; //�����ĸ����־�ֹ��������Ϊ�뾶(r=100)��ת��45��ľ���


const rt_int32_t dis_for_tlf_left45 = 1492;
const rt_int32_t dis_for_tlf_right45 = 1649;

const rt_int32_t dis_for_tri_left45 = dis_for_tlf_right45;
const rt_int32_t dis_for_tri_right45 = dis_for_tlf_left45; //�������˶�ʱ��������Ϊ�뾶��r=2000����ת��45��ľ���

const rt_int32_t dis_for_tlf_left = 0;
const rt_int32_t dis_for_tlf_right = 0;

const rt_int32_t dis_for_tri_left = dis_for_tlf_right;
const rt_int32_t dis_for_tri_right = dis_for_tlf_left;

const rt_int32_t dis_back_tlf_left = dis_for_tlf_right;
const rt_int32_t dis_back_tlf_right = dis_for_tlf_left;

const rt_int32_t dis_back_tri_left = dis_for_tlf_left;
const rt_int32_t dis_back_tri_right = dis_for_tlf_right;//�������˶�ʱ��������Ϊ�뾶��ת��180��ľ���(���ã� //��ʱ��ֱ��ת180�� ����������

const rt_int32_t dis_big_tlf_left = 5882;
const rt_int32_t dis_big_tlf_right = 5183;

const rt_int32_t dis_big_tri_left = dis_big_tlf_right;
const rt_int32_t dis_big_tri_right = dis_big_tlf_left;

const rt_int32_t be_to_left1 = 1646;
const rt_int32_t left1_to_left3 = 1696;
const rt_int32_t left3_to_left2 = 1400;//��ʱ����

const rt_int32_t left2_to_right2 = 1400;//��ʱ����
const rt_int32_t right2_to_right3 = 1960;//��ʱ����

const rt_int32_t right3_to_right1 = 1696;
const rt_int32_t right1_to_be = 1646;

//��ȥ�ұ�
const rt_int32_t be_to_right1 = 1646;
const rt_int32_t right1_to_right3 = 1696;
const rt_int32_t right3_to_right2 = 1400;//��ʱ����

const rt_int32_t right2_to_left2 = 1400;//��ʱ����
const rt_int32_t left2_to_left3 = 1960;//��ʱ����

const rt_int32_t left3_to_left1 = 1696;
const rt_int32_t left1_to_be = 1646;
