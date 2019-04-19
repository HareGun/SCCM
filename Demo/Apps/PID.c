/**
  ******************************************************************************
  * @file    PID.c
  * @author  Hare
  * @version V1.0
  * @date    2019-01-15
  * @brief   PID算法
  ******************************************************************************
  */

#include "PID.h"


/**
  * @brief  绝对值限幅
  * @param       p_a  要限幅的值
  * @param[in]   absMax  最大值
  * @retval None
  */
static void abs_limit(float *p_a, float absMax){
  if(*p_a > absMax)
    *p_a = absMax;
  if(*p_a < -absMax)
    *p_a = -absMax;
}

/**
  * @brief  增量式PID参数设置(全部清零)
  * @param       pid_t  增量式pid结构体
  * @param[in]   kp,ki,kd  pid参数
  * @param[in]   maxOutput 输出限幅
  * @param[in]   integralLimit 积分限幅
  * @retval None
  */
void IncrementalPID_paraReset(incrementalpid_t *pid_t, float kp, float ki, float kd, uint32_t maxOutput, uint32_t integralLimit){
	pid_t->target = 0;
	pid_t->measured = 0;
	pid_t->err = 0;
	pid_t->err_last = 0;
	pid_t->err_beforeLast = 0;
	pid_t->Kp = kp;
	pid_t->Ki = ki;
	pid_t->Kd = kd;
	pid_t->maxOutput = maxOutput;
	pid_t->integralLimit = integralLimit;
	pid_t->out = 0; 			
}

/**
  * @brief  增量式PID参数设置(不清零目标，测量值)
  * @param       pid_t  增量式pid结构体
  * @param[in]   kp,ki,kd  pid参数
  * @retval None
  */
void IncrementalPID_setPara(incrementalpid_t *pid_t, float kp, float ki, float kd){
	pid_t->err = 0;
	pid_t->err_last = 0;
	pid_t->err_beforeLast = 0;
	pid_t->Kp = kp;
	pid_t->Ki = ki;
	pid_t->Kd = kd;	
	pid_t->out = 0;	
}


float Incremental_PID(incrementalpid_t *pid_t, float target, float measured) {
	float p_out, i_out, d_out;
	pid_t->target = target;
	pid_t->measured = measured;
	pid_t->err = pid_t->target - pid_t->measured;
	
//	if(abs(pid_t->err)<0.1f)
//		pid_t->err = 0.0f;
//  return 0;
	
	p_out = pid_t->Kp*(pid_t->err - pid_t->err_last);
	i_out = pid_t->Ki*pid_t->err;
	d_out = pid_t->Kd*(pid_t->err - 2.0f*pid_t->err_last + pid_t->err_beforeLast);
	
	//积分限幅
	abs_limit(&i_out, pid_t->integralLimit);
	
	pid_t->out += (p_out + i_out + d_out);
	
	//输出限幅
	abs_limit(&pid_t->out, pid_t->maxOutput);
	
	pid_t->err_beforeLast = pid_t->err_last;
	pid_t->err_last = pid_t->err;

	return pid_t->out;
}

void PositionPID_paraReset(positionpid_t *pid_t, float kp, float ki, float kd, uint32_t maxOutput, uint32_t integralLimit){
	pid_t->target = 0;
	pid_t->measured = 0;
	pid_t->maxOutput = maxOutput;
	pid_t->integralLimit = integralLimit;
	pid_t->err = 0;
	pid_t->err_last = 0;
	pid_t->integral_err = 0;
	pid_t->Kp = kp;
	pid_t->Ki = ki;
	pid_t->Kd = kd;
	pid_t->out = 0; 			
}

void PositionPID_setPara(positionpid_t *pid_t, float kp, float ki, float kd){
	pid_t->err = 0;
	pid_t->err_last = 0;
	pid_t->integral_err = 0;
	pid_t->Kp = kp;
	pid_t->Ki = ki;
	pid_t->Kd = kd;		
	pid_t->out = 0;	
}


float Position_PID(positionpid_t *pid_t, float target, float measured) {
	float p_out, i_out, d_out;
	pid_t->target = (float)target;
	pid_t->measured = (float)measured;
	pid_t->err = pid_t->target - pid_t->measured;
  
  /* 防止积分饱和 */
  if(abs(pid_t->out) < pid_t->maxOutput)
  {
      pid_t->integral_err += pid_t->err;
  }
  else{
    if(pid_t->out > 0 && pid_t->err < 0)
    {
      pid_t->integral_err += pid_t->err;
    }
    else if(pid_t->out < 0 && pid_t->err > 0)
    {
      pid_t->integral_err += pid_t->err;
    }
  }
	
	
	p_out = pid_t->Kp*pid_t->err;
	i_out = pid_t->Ki*pid_t->integral_err;
	d_out = pid_t->Kd*(pid_t->err - pid_t->err_last);
	
	//积分限幅
	abs_limit(&i_out, pid_t->integralLimit);
	
	pid_t->out = (p_out + i_out + d_out);
	
	//输出限幅
	abs_limit(&pid_t->out, pid_t->maxOutput);
	
	pid_t->err_last = pid_t->err;
	
	return pid_t->out;
}

