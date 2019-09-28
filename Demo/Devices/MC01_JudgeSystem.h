#ifndef __MC02_JUDGESYSTEM_H
#define __MC02_JUDGESYSTEM_H

#include "user_common.h"

#define JUDGESYSTEM_PACKSIZE 				180u		    /* ����ϵͳ����С */
#define JUDGESYSTEM_FRAMEHEADER    	0xA5        /* ֡ͷ */

/* ����ϵͳCmdID */
#define JUDGESYS_CMDID_GAMESTATUS     0x0001u     /* ����״̬���ݣ�1Hz ���ڷ��� */
#define JUDGESYS_CMDID_GAMERESULT     0x0002u     /* ����������ݣ������������� */
#define JUDGESYS_CMDID_ROBOTLIVEINFO  0x0003u     /* ���������˴�����ݣ�1Hz ���ڷ��� */
#define JUDGESYS_CMDID_AREAEVENT      0x0101u     /* �����¼����ݣ��¼��ı���� */
#define JUDGESYS_CMDID_SUPPLYACTION   0x0102u     /* ���ز���վ������ʶ���ݣ������ı���� */
#define JUDGESYS_CMDID_SUPPLYREQ      0x0103u     /* ���󲹸�վ�������ݣ��ɲ����ӷ��ͣ����� 10Hz����RM �Կ�����δ���ţ� */
#define JUDGESYS_CMDID_ROBOTSTATUS    0x0201u     /* ������״̬���ݣ�10Hz ���ڷ��� */
#define JUDGESYS_CMDID_POWERHEAT      0x0202u     /* ʵʱ�����������ݣ�50Hz ���ڷ��� */
#define JUDGESYS_CMDID_ROBOTPOS       0x0203u     /* ������λ�����ݣ�10Hz ���� */
#define JUDGESYS_CMDID_BUFF           0x0204u     /* �������������ݣ�����״̬�ı���� */
#define JUDGESYS_CMDID_AERIALENERGY   0x0205u     /* ���л���������״̬���ݣ�10Hz ���ڷ��ͣ�ֻ�п��л��������ط��� */
#define JUDGESYS_CMDID_HURTINFO       0x0206u     /* �˺�״̬���ݣ��˺��������� */
#define JUDGESYS_CMDID_SHOOTINFO      0x0207u     /* ʵʱ������ݣ��ӵ�������� */
#define JUDGESYS_CMDID_ROBOTCOMINFO   0x0301u     /* �������ݣ����ͷ��������ͣ����� 10Hz */

#define JUDGESYS_DATAID_CLIENTUPLOAD  0xD180u     /* �ϴ��ͻ���������ʾ������ID */
#define JUDGESYS_DATAID_ROBOTCOM_MIN  0x0200u 		/* �����˼����ݽ���������ID����Сֵ */
#define JUDGESYS_DATAID_ROBOTCOM_MAX  0x02FFu		  /* �����˼����ݽ���������ID�����ֵ */

/* ���ݻ�������  FrameHeader(5-Byte)+CmdID(2-Byte)+FrameTail(2-Byte, CRC16, ����У��)*/
#define JUDGESYS_DATALENGTH_BASE               9     

/* ����֡�ĳ��� Data(n-Byte)*/
#define JUDGESYS_DATALENGTH_GAMESTATUS    	   3
#define JUDGESYS_DATALENGTH_GAMERESULT     	   1
#define JUDGESYS_DATALENGTH_ROBOTLIVEINFO 	   2
#define JUDGESYS_DATALENGTH_AREAEVENT     	 	 4
#define JUDGESYS_DATALENGTH_SUPPLYACTION  		 4
#define JUDGESYS_DATALENGTH_SUPPLYREQ      	   3
#define JUDGESYS_DATALENGTH_ROBOTSTATUS        15
#define JUDGESYS_DATALENGTH_POWERHEAT     	   14
#define JUDGESYS_DATALENGTH_ROBOTPOS 					 16
#define JUDGESYS_DATALENGTH_BUFF         			 1
#define JUDGESYS_DATALENGTH_AERIALENERGY  		 3
#define JUDGESYS_DATALENGTH_HURTINFO     		   1
#define JUDGESYS_DATALENGTH_SHOOTINFO    		   6

#define JUDGESYS_DATALENGTH_ROBOTCOMHEADER     6
#define JUDGESYS_DATALENGTH_CLIENTUPLOADINFO	 19
#define JUDGESYS_DATALENGTH_ROBOTCOMINFO  	 	 119

/* ��������֡�ĳ��ȣ�FrameHeader(5-Byte)+CmdID(2-Byte)+Data(n-Byte)+FrameTail(2-Byte, CRC16, ����У��) */
#define JUDGESYS_FULLDATALENGTH_GAMESTATUS		 	 (JUDGESYS_DATALENGTH_GAMESTATUS + JUDGESYS_DATALENGTH_BASE)
#define JUDGESYS_FULLDATALENGTH_GAMERESULT 			 (JUDGESYS_DATALENGTH_GAMERESULT + JUDGESYS_DATALENGTH_BASE)
#define JUDGESYS_FULLDATALENGTH_ROBOTLIVEINFO 	 (JUDGESYS_DATALENGTH_ROBOTLIVEINFO + JUDGESYS_DATALENGTH_BASE)
#define JUDGESYS_FULLDATALENGTH_AREAEVENT 			 (JUDGESYS_DATALENGTH_AREAEVENT + JUDGESYS_DATALENGTH_BASE)
#define JUDGESYS_FULLDATALENGTH_SUPPLYACTION 		 (JUDGESYS_DATALENGTH_SUPPLYACTION + JUDGESYS_DATALENGTH_BASE)
#define JUDGESYS_FULLDATALENGTH_SUPPLYREQ 			 (JUDGESYS_DATALENGTH_SUPPLYREQ + JUDGESYS_DATALENGTH_BASE)
#define JUDGESYS_FULLDATALENGTH_ROBOTSTATUS 		 (JUDGESYS_DATALENGTH_ROBOTSTATUS + JUDGESYS_DATALENGTH_BASE)
#define JUDGESYS_FULLDATALENGTH_POWERHEAT 			 (JUDGESYS_DATALENGTH_POWERHEAT + JUDGESYS_DATALENGTH_BASE)
#define JUDGESYS_FULLDATALENGTH_ROBOTPOS 				 (JUDGESYS_DATALENGTH_ROBOTPOS + JUDGESYS_DATALENGTH_BASE)
#define JUDGESYS_FULLDATALENGTH_BUFF 						 (JUDGESYS_DATALENGTH_BUFF + JUDGESYS_DATALENGTH_BASE)
#define JUDGESYS_FULLDATALENGTH_AERIALENERGY 		 (JUDGESYS_DATALENGTH_AERIALENERGY + JUDGESYS_DATALENGTH_BASE)
#define JUDGESYS_FULLDATALENGTH_HURTINFO 				 (JUDGESYS_DATALENGTH_HURTINFO + JUDGESYS_DATALENGTH_BASE)
#define JUDGESYS_FULLDATALENGTH_SHOOTINFO			   (JUDGESYS_DATALENGTH_SHOOTINFO + JUDGESYS_DATALENGTH_BASE)
#define JUDGESYS_FULLDATALENGTH_CLIENTUPLOADINFO (JUDGESYS_DATALENGTH_CLIENTUPLOADINFO + JUDGESYS_DATALENGTH_BASE)
#define JUDGESYS_FULLDATALENGTH_ROBOTCOMINFO  	 (JUDGESYS_DATALENGTH_ROBOTCOMINFO + JUDGESYS_DATALENGTH_BASE)

/* ����״̬���ݣ�����Ƶ�ʣ�10Hz, CmdID 0x0001 */
typedef struct{
	union {
		uint8_t dataBuff[JUDGESYS_DATALENGTH_GAMESTATUS];
		struct{
			uint8_t game_type : 4; 			/* �������� */
			uint8_t game_progress : 4;	/* ��ǰ�����׶� */
			uint16_t stage_remain_time; /* ��ǰ�׶�ʣ��ʱ�� */
		};
	}data;
	uint8_t infoUpdateFlag;
}JudgeSYS_GameStatus_t;

/* ����������ݣ���������ʱ���� CmdID 0x0002 */
typedef struct
{
	uint8_t winner; 	/* ������� */
	uint8_t infoUpdateFlag;
}JudgeSYS_GameResult_t;

/* �����˴�����ݣ�����Ƶ�ʣ�1Hz, CmdID 0x0002 */
/* ��Ӧ�� bit ��ֵ�� 1 ��������˴���ֵ�� 0 �����������������δ�ϳ� */
typedef struct
{
	union {
		uint16_t dataBuff;
		struct{
			uint8_t redHero : 1;
			uint8_t redEngineer : 1;
			uint8_t redInfantry1 : 1;
			uint8_t redInfantry2 : 1;
			uint8_t redInfantry3 : 1;
			uint8_t redAerial : 1;
			uint8_t redSentry : 1;
			uint8_t reserve_7 : 1;
			uint8_t blueHero : 1;
			uint8_t blueEngineer : 1;
			uint8_t blueInfantry1 : 1;
			uint8_t blueInfantry2 : 1;
			uint8_t blueInfantry3 : 1;
			uint8_t blueAerial : 1;
			uint8_t blueSentry : 1;
			uint8_t reserve_15 : 1;
		};
	}data;
	uint8_t infoUpdateFlag;
}JudgeSYS_RobotLiveInfo_t;

/* �����¼����ݣ��¼��ı���� CmdID 0x0101 */
typedef struct
{
	union {
		uint32_t dataBuff;
		struct
		{
			uint8_t apron : 2;		/* ����ͣ��ƺռ��״̬,0δռ�죬1ռ��δͣ����2ռ����ͣ�� */
			uint8_t recoveryPoint1 : 1; /* ������Ѫ��1,2,3ռ��״̬, 1 Ϊ��ռ�� */
			uint8_t recoveryPoint2 : 1;
			uint8_t recoveryPoint3 : 1;
			uint8_t energyAgency : 2; /* ������������״̬,0δռ��δ���1ռ��δ���2δռ���Ѽ��3ռ���Ѽ��� */
			uint8_t gateway : 1;			/* �����ؿ�ռ��״̬, 1 Ϊ��ռ�� */
			uint8_t blockhouse : 1;		/* �����ﱤռ��״̬, 1 Ϊ��ռ�� */
			uint8_t resource_island : 1; /* ������Դ��ռ��״̬, 1 Ϊ��ռ�� */
			uint8_t base_status : 2;		 /* ��������״̬,0�޷�����1���ڱ�������2 100%���� */
			uint8_t ICRA_red_buff : 2;
			uint8_t ICRA_blue_buff : 2;
		};
	} data;
	uint8_t infoUpdateFlag;
}JudgeSYS_AeraEvent_t;

/* ����վ������ʶ�������ı���� CmdID 0x0102 */
typedef struct
{
	union {
		uint8_t dataBuff[JUDGESYS_DATALENGTH_SUPPLYACTION];
		struct
		{
			uint8_t supply_id;			 		/* ����վ�� ID */
			uint8_t supply_robot_id; 		/* ���������� ID */
			uint8_t supply_status;			/* �����ڿ���״̬ */
			uint8_t supply_bullet_num;	/* �������� */
		};
	} data;
	uint8_t infoUpdateFlag;
}JudgeSYS_SupplyAction_t;

/* ���󲹸�վ�����ӵ�������Ƶ�ʣ�����10Hz CmdID 0x0103 */
typedef struct
{
	union {
		uint8_t dataBuff[JUDGESYS_DATALENGTH_SUPPLYREQ];
		struct
		{
			uint8_t supply_id;				 /* ����վ�� ID */
			uint8_t supply_robot_id;	 /* ���������� ID */
			uint8_t supply_bullet_num; /* �������� */
		};
	} data;
	uint8_t infoUpdateFlag;
}JudgeSYS_SupplyReq_t;

/* ����������״̬������Ƶ��10Hz CmdID 0x0201 */
typedef struct
{
	union {
		uint8_t dataBuff[JUDGESYS_DATALENGTH_ROBOTSTATUS];
		struct
		{
			uint8_t robot_id;
			uint8_t robot_level;
			uint16_t remain_HP;
			uint16_t max_HP;
			uint16_t shooter_heat0_cooling_rate;
			uint16_t shooter_heat0_cooling_limit;
			uint16_t shooter_heat1_cooling_rate;
			uint16_t shooter_heat1_cooling_limit;
			uint8_t mains_power_gimbal_output : 1;
			uint8_t mains_power_chassis_output : 1;
			uint8_t mains_power_shooter_output : 1;
		};
	} data;
	uint8_t infoUpdateFlag;
}JudgeSYS_RobotStatus_t;

/* ʵʱ���ʺ��������ݣ�����Ƶ��50Hz CmdID 0x0202 */
typedef struct
{
	union {
		uint8_t dataBuff[JUDGESYS_DATALENGTH_POWERHEAT];
		struct
		{
			uint16_t chassis_volt; 					/* ���������ѹ ��λ ���� */
			uint16_t chassis_current; 			/* ����������� ��λ ���� */
			float chassis_power;						/* ����������� ��λ �� */
			uint16_t chassis_power_buffer;  /* ���̹��ʻ��� ��λ ���� */
			uint16_t shooter_heat0;				  /* 17mm ǹ������ */
			uint16_t shooter_heat1;				  /* 42mm ǹ������ */
		};
	} data;
	uint8_t infoUpdateFlag;
}JudgeSYS_PowerHeatData_t;

/* ������λ�ú�ǹ�ڳ�����Ϣ������Ƶ��10Hz CmdID 0x0203 */
typedef struct
{
	union {
		uint8_t dataBuff[JUDGESYS_DATALENGTH_ROBOTPOS];
		struct
		{
			float x;			/* xλ�����꣬��λ m */
			float y;			/* yλ�����꣬��λ m */
			float z;			/* zλ�����꣬��λ m */
			float yaw; 		/* ǹ�ڳ���Ƕȣ���λ �� */
		};
	} data;
	uint8_t infoUpdateFlag;
}JudgeSYS_RobotPos_t;

/* ���������棬״̬�ı���� CmdID 0x0204 */
typedef struct{
	union {
		uint8_t dataBuff;
		struct{
			uint8_t recovery_buff : 1;			/* ������Ѫ����Ѫ״̬ */
			uint8_t heat_cooling_buff : 1;	/* ǹ��������ȴ���� */
			uint8_t defense_buff : 1;				/* �����˷����ӳ� */
			uint8_t attack_buff : 1;				/* �����˹����ӳ� */
		};
	}data;
	uint8_t infoUpdateFlag;
}JudgeSYS_RobotBuff_t;

/* ���л���������״̬,����Ƶ��10Hz CmdID 0x0205 */
typedef struct
{
	union {
		uint8_t dataBuff[JUDGESYS_DATALENGTH_AERIALENERGY];
		struct
		{
			uint8_t energy_point; /* ���۵������� */
			uint8_t attack_time;	/* �ɹ���ʱ�� ��λ s */
		};
	} data;
	uint8_t infoUpdateFlag;
}JudgeSYS_AerialEnergy_t;

/* �˺�״̬���˺��������� CmdID 0x0206 */
typedef struct
{
	union {
		uint8_t dataBuff;
	  struct
		{
			uint8_t armor_id : 4;
			uint8_t hurt_type : 4;
		};
	} data;
	uint8_t infoUpdateFlag;
} JudgeSYS_HurtInfo_t;

/* ʵʱ������ݣ�������� CmdID 0x0207 */
typedef struct{
	union {
		uint8_t dataBuff[JUDGESYS_DATALENGTH_SHOOTINFO];
		struct{
			uint8_t bulletType;		/* �������� 1��17mm ���� 2��42mm ���� */
			uint8_t bulletFreq;		/* ������Ƶ����λ��Hz */
			float bulletSpeed;		/* �������٣���λ����ÿ�� */
		};
	}data;
	uint8_t infoUpdateFlag;
}JudgeSYS_ShootInfo_t;


//�������Զ�����������ͷ�����ڻ����˼�����ͨ�ţ���Ƶ 10Hz CmdID 0x0301
typedef struct
{
	union {
		uint8_t dataBuff[JUDGESYS_DATALENGTH_ROBOTCOMHEADER];
		struct
		{
			uint16_t data_cmd_id; /* ���ݶε����� ID  */
			uint16_t send_ID;			/* �����ߵ� ID  */
			uint16_t receiver_ID; /* �����ߵ� ID  */
		};
	} data;
	uint8_t infoUpdateFlag;
}JudgeSYS_RobotComHeader_t;

/* �������Զ������ݣ�������ʾ�ڲ������棬��Ƶ 10Hz CmdID 0x0301 */
typedef struct{
	union {
		uint8_t dataBuff[JUDGESYS_DATALENGTH_CLIENTUPLOADINFO];
		struct{
			uint16_t data_cmd_id; /* ���ݶε����� ID  */
			uint16_t send_ID;			/* �����ߵ� ID  */
			uint16_t receiver_ID; /* �����ߵ� ID  */
			float data1;
			float data2;
			float data3;
			uint8_t mask;
		};
	}data;
	uint8_t infoUpdateFlag;
}JudgeSYS_ClientUploadInfo_t;



//����ϵͳ����
typedef struct{
	JudgeSYS_GameStatus_t GameStatus;
	JudgeSYS_GameResult_t GameResult;
	JudgeSYS_RobotLiveInfo_t RobotLiveInfo;
	JudgeSYS_AeraEvent_t AeraEvent;
	JudgeSYS_SupplyAction_t SupplyAction;
	JudgeSYS_SupplyReq_t SupplyReq;
	JudgeSYS_RobotStatus_t RobotStatus;
	JudgeSYS_PowerHeatData_t PowerHeatData;
	JudgeSYS_RobotPos_t RobotPos;
	JudgeSYS_RobotBuff_t RobotBuff;
	JudgeSYS_AerialEnergy_t AerialEnergy;
	JudgeSYS_HurtInfo_t HurtInfo;
	JudgeSYS_ShootInfo_t ShootInfo;
	JudgeSYS_ClientUploadInfo_t ClientUploadInfo;
	JudgeSYS_RobotComHeader_t RobotComInfo_RX;
  JudgeSYS_RobotComHeader_t RobotComInfo_TX;
  uint8_t sendDataCounter;      /* ���ڱ�ǰ���� */
	uint16_t infoUpdateFrame;     /* ֡�� */
	uint8_t offLineFlag;		      /* �豸���߱�־ */
}JudgeSYS_t;




extern JudgeSYS_t JudgeSYS;

void JudgeSystem_Init(void);
void Judge_getInfo(uint16_t dataLength);
void Judge_sendInfo(void);




#endif /* __MC02_JUDGESYSTEM_H */
