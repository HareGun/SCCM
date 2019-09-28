#ifndef __MC02_JUDGESYSTEM_H
#define __MC02_JUDGESYSTEM_H

#include "user_common.h"

#define JUDGESYSTEM_PACKSIZE 				180u		    /* 裁判系统包大小 */
#define JUDGESYSTEM_FRAMEHEADER    	0xA5        /* 帧头 */

/* 裁判系统CmdID */
#define JUDGESYS_CMDID_GAMESTATUS     0x0001u     /* 比赛状态数据，1Hz 周期发送 */
#define JUDGESYS_CMDID_GAMERESULT     0x0002u     /* 比赛结果数据，比赛结束后发送 */
#define JUDGESYS_CMDID_ROBOTLIVEINFO  0x0003u     /* 比赛机器人存活数据，1Hz 周期发送 */
#define JUDGESYS_CMDID_AREAEVENT      0x0101u     /* 场地事件数据，事件改变后发送 */
#define JUDGESYS_CMDID_SUPPLYACTION   0x0102u     /* 场地补给站动作标识数据，动作改变后发送 */
#define JUDGESYS_CMDID_SUPPLYREQ      0x0103u     /* 请求补给站补弹数据，由参赛队发送，上限 10Hz。（RM 对抗赛尚未开放） */
#define JUDGESYS_CMDID_ROBOTSTATUS    0x0201u     /* 机器人状态数据，10Hz 周期发送 */
#define JUDGESYS_CMDID_POWERHEAT      0x0202u     /* 实时功率热量数据，50Hz 周期发送 */
#define JUDGESYS_CMDID_ROBOTPOS       0x0203u     /* 机器人位置数据，10Hz 发送 */
#define JUDGESYS_CMDID_BUFF           0x0204u     /* 机器人增益数据，增益状态改变后发送 */
#define JUDGESYS_CMDID_AERIALENERGY   0x0205u     /* 空中机器人能量状态数据，10Hz 周期发送，只有空中机器人主控发送 */
#define JUDGESYS_CMDID_HURTINFO       0x0206u     /* 伤害状态数据，伤害发生后发送 */
#define JUDGESYS_CMDID_SHOOTINFO      0x0207u     /* 实时射击数据，子弹发射后发送 */
#define JUDGESYS_CMDID_ROBOTCOMINFO   0x0301u     /* 交互数据，发送方触发发送，上限 10Hz */

#define JUDGESYS_DATAID_CLIENTUPLOAD  0xD180u     /* 上传客户端数据显示的内容ID */
#define JUDGESYS_DATAID_ROBOTCOM_MIN  0x0200u 		/* 机器人间数据交换的内容ID，最小值 */
#define JUDGESYS_DATAID_ROBOTCOM_MAX  0x02FFu		  /* 机器人间数据交换的内容ID，最大值 */

/* 数据基本长度  FrameHeader(5-Byte)+CmdID(2-Byte)+FrameTail(2-Byte, CRC16, 整包校验)*/
#define JUDGESYS_DATALENGTH_BASE               9     

/* 数据帧的长度 Data(n-Byte)*/
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

/* 整个数据帧的长度，FrameHeader(5-Byte)+CmdID(2-Byte)+Data(n-Byte)+FrameTail(2-Byte, CRC16, 整包校验) */
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

/* 比赛状态数据，发送频率：10Hz, CmdID 0x0001 */
typedef struct{
	union {
		uint8_t dataBuff[JUDGESYS_DATALENGTH_GAMESTATUS];
		struct{
			uint8_t game_type : 4; 			/* 比赛类型 */
			uint8_t game_progress : 4;	/* 当前比赛阶段 */
			uint16_t stage_remain_time; /* 当前阶段剩余时间 */
		};
	}data;
	uint8_t infoUpdateFlag;
}JudgeSYS_GameStatus_t;

/* 比赛结果数据，比赛结束时推送 CmdID 0x0002 */
typedef struct
{
	uint8_t winner; 	/* 比赛结果 */
	uint8_t infoUpdateFlag;
}JudgeSYS_GameResult_t;

/* 机器人存活数据，发送频率：1Hz, CmdID 0x0002 */
/* 对应的 bit 数值置 1 代表机器人存活，数值置 0 代表机器人死亡或者未上场 */
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

/* 场地事件数据，事件改变后发送 CmdID 0x0101 */
typedef struct
{
	union {
		uint32_t dataBuff;
		struct
		{
			uint8_t apron : 2;		/* 己方停机坪占领状态,0未占领，1占领未停浆，2占领已停浆 */
			uint8_t recoveryPoint1 : 1; /* 己方补血点1,2,3占领状态, 1 为已占领 */
			uint8_t recoveryPoint2 : 1;
			uint8_t recoveryPoint3 : 1;
			uint8_t energyAgency : 2; /* 己方能量机关状态,0未占领未激活，1占领未激活，2未占领已激活，3占领已激活 */
			uint8_t gateway : 1;			/* 己方关口占领状态, 1 为已占领 */
			uint8_t blockhouse : 1;		/* 己方碉堡占领状态, 1 为已占领 */
			uint8_t resource_island : 1; /* 己方资源岛占领状态, 1 为已占领 */
			uint8_t base_status : 2;		 /* 己方基地状态,0无防御，1有哨兵防御，2 100%防御 */
			uint8_t ICRA_red_buff : 2;
			uint8_t ICRA_blue_buff : 2;
		};
	} data;
	uint8_t infoUpdateFlag;
}JudgeSYS_AeraEvent_t;

/* 补给站动作标识，动作改变后发送 CmdID 0x0102 */
typedef struct
{
	union {
		uint8_t dataBuff[JUDGESYS_DATALENGTH_SUPPLYACTION];
		struct
		{
			uint8_t supply_id;			 		/* 补给站口 ID */
			uint8_t supply_robot_id; 		/* 补弹机器人 ID */
			uint8_t supply_status;			/* 出弹口开闭状态 */
			uint8_t supply_bullet_num;	/* 补弹数量 */
		};
	} data;
	uint8_t infoUpdateFlag;
}JudgeSYS_SupplyAction_t;

/* 请求补给站补弹子弹，发送频率：上限10Hz CmdID 0x0103 */
typedef struct
{
	union {
		uint8_t dataBuff[JUDGESYS_DATALENGTH_SUPPLYREQ];
		struct
		{
			uint8_t supply_id;				 /* 补给站口 ID */
			uint8_t supply_robot_id;	 /* 补弹机器人 ID */
			uint8_t supply_bullet_num; /* 补弹数量 */
		};
	} data;
	uint8_t infoUpdateFlag;
}JudgeSYS_SupplyReq_t;

/* 比赛机器人状态，发送频率10Hz CmdID 0x0201 */
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

/* 实时功率和热量数据，发送频率50Hz CmdID 0x0202 */
typedef struct
{
	union {
		uint8_t dataBuff[JUDGESYS_DATALENGTH_POWERHEAT];
		struct
		{
			uint16_t chassis_volt; 					/* 底盘输出电压 单位 毫伏 */
			uint16_t chassis_current; 			/* 底盘输出电流 单位 毫安 */
			float chassis_power;						/* 底盘输出功率 单位 瓦 */
			uint16_t chassis_power_buffer;  /* 底盘功率缓冲 单位 焦耳 */
			uint16_t shooter_heat0;				  /* 17mm 枪口热量 */
			uint16_t shooter_heat1;				  /* 42mm 枪口热量 */
		};
	} data;
	uint8_t infoUpdateFlag;
}JudgeSYS_PowerHeatData_t;

/* 机器人位置和枪口朝向信息，发送频率10Hz CmdID 0x0203 */
typedef struct
{
	union {
		uint8_t dataBuff[JUDGESYS_DATALENGTH_ROBOTPOS];
		struct
		{
			float x;			/* x位置坐标，单位 m */
			float y;			/* y位置坐标，单位 m */
			float z;			/* z位置坐标，单位 m */
			float yaw; 		/* 枪口朝向角度，单位 度 */
		};
	} data;
	uint8_t infoUpdateFlag;
}JudgeSYS_RobotPos_t;

/* 机器人增益，状态改变后发送 CmdID 0x0204 */
typedef struct{
	union {
		uint8_t dataBuff;
		struct{
			uint8_t recovery_buff : 1;			/* 机器人血量补血状态 */
			uint8_t heat_cooling_buff : 1;	/* 枪口热量冷却加速 */
			uint8_t defense_buff : 1;				/* 机器人防御加成 */
			uint8_t attack_buff : 1;				/* 机器人攻击加成 */
		};
	}data;
	uint8_t infoUpdateFlag;
}JudgeSYS_RobotBuff_t;

/* 空中机器人能量状态,发送频率10Hz CmdID 0x0205 */
typedef struct
{
	union {
		uint8_t dataBuff[JUDGESYS_DATALENGTH_AERIALENERGY];
		struct
		{
			uint8_t energy_point; /* 积累的能量点 */
			uint8_t attack_time;	/* 可攻击时间 单位 s */
		};
	} data;
	uint8_t infoUpdateFlag;
}JudgeSYS_AerialEnergy_t;

/* 伤害状态，伤害发生后发送 CmdID 0x0206 */
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

/* 实时射击数据，射击后发送 CmdID 0x0207 */
typedef struct{
	union {
		uint8_t dataBuff[JUDGESYS_DATALENGTH_SHOOTINFO];
		struct{
			uint8_t bulletType;		/* 弹丸类型 1：17mm 弹丸 2：42mm 弹丸 */
			uint8_t bulletFreq;		/* 弹丸射频，单位：Hz */
			float bulletSpeed;		/* 弹丸射速，单位：米每秒 */
		};
	}data;
	uint8_t infoUpdateFlag;
}JudgeSYS_ShootInfo_t;


//参赛队自定义数据数据头，用于机器人间数据通信，限频 10Hz CmdID 0x0301
typedef struct
{
	union {
		uint8_t dataBuff[JUDGESYS_DATALENGTH_ROBOTCOMHEADER];
		struct
		{
			uint16_t data_cmd_id; /* 数据段的内容 ID  */
			uint16_t send_ID;			/* 发送者的 ID  */
			uint16_t receiver_ID; /* 接收者的 ID  */
		};
	} data;
	uint8_t infoUpdateFlag;
}JudgeSYS_RobotComHeader_t;

/* 参赛队自定义数据，用于显示在操作界面，限频 10Hz CmdID 0x0301 */
typedef struct{
	union {
		uint8_t dataBuff[JUDGESYS_DATALENGTH_CLIENTUPLOADINFO];
		struct{
			uint16_t data_cmd_id; /* 数据段的内容 ID  */
			uint16_t send_ID;			/* 发送者的 ID  */
			uint16_t receiver_ID; /* 接收者的 ID  */
			float data1;
			float data2;
			float data3;
			uint8_t mask;
		};
	}data;
	uint8_t infoUpdateFlag;
}JudgeSYS_ClientUploadInfo_t;



//裁判系统数据
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
  uint8_t sendDataCounter;      /* 用于标记包序号 */
	uint16_t infoUpdateFrame;     /* 帧率 */
	uint8_t offLineFlag;		      /* 设备离线标志 */
}JudgeSYS_t;




extern JudgeSYS_t JudgeSYS;

void JudgeSystem_Init(void);
void Judge_getInfo(uint16_t dataLength);
void Judge_sendInfo(void);




#endif /* __MC02_JUDGESYSTEM_H */
