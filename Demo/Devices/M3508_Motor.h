#ifndef __M3508_MOTOR_H
#define __M3508_MOTOR_H

#include "user_common.h"

typedef struct{
	uint16_t realAngle;			//�������Ļ�е�Ƕ�
	int16_t realSpeed;			//���������ٶ�
	int16_t realCurrent;		//��������ʵ�ʵ���
	uint8_t temperture;			//�������ĵ���¶�
  uint16_t lastAngle;			//�ϴεĽǶ�
	int32_t totalAngle;			//�ۻ��ܹ��Ƕ�
	int16_t turnCount;			//ת����Ȧ��
	int16_t targetSpeed;			//Ŀ���ٶ�
	int32_t targetAngle;			//Ŀ��Ƕ�
	int16_t outCurrent;				//�������
	positionpid_t pid_speed;		//����ٶ�pid
	positionpid_t pid_angle;		//�Ƕȵ��pid
	uint8_t infoUpdateFlag;		//��Ϣ��ȡ���±�־
	uint16_t infoUpdateFrame;	//֡��
	uint8_t offLineFlag;		//�豸���߱�־
}M3508s_t;

#define M3508_CurrentRatio	819.2f	//16384/20A = 819.2->1A
//#define M3508_FIRSTANGLE		3800		/* �����ʼλ�� */

/* �Ƕ�ת������ֵ */
#define M3508_ANGLE_TO_ENCODER(x)   (8192.0f/360.0f * x)

/* ���ٺ�Ƕ�ת������ֵ */
#define M3508_P19ANGLE_TO_ENCODER(x)   (x/19.0f * 8192.0f)

//void M3508_setCurrent(int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4);/* �������� */
void M3508_getInfo(M3508s_t *p_M3508, CanRxMsg RxMessage);
int32_t M3508_clearTurnCounter(M3508s_t *p_M3508);


#endif /* __M3508_MOTOR_H */
