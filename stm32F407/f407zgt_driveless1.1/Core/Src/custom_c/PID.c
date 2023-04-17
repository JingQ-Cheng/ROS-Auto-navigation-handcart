
#include "custom_h/all_header.h"

//float pid[0]=100,pid[1]=0,pid[2]=0;
uint8_t pid_count;
//float pid[3] ={21,1,-15};
float pid[3] ={4,0,-1.2};


//int dsp_PID(float position,float target)
//{
//	static arm_pid_instance_f32 PID;
//	 PID.Kp = pid[0]; 			/* Proporcional --比例参数 */
//	 PID.Ki = pid[1];         /* Integral         --积分参数*/
//	 PID.Kd = pid[2]; 			/* Derivative     --微分参数*/
//	 arm_pid_init_f32(&PID, 1);
//	 float pid_error = target - position;
//
//	 float32_t output = arm_pid_f32(&PID, pid_error);
////	 arm_pid_reset_f32(&PID);
//
//	 return output;
//}



/*实现前馈控制器*/
int FeedforwardController(float target_in)
{
	static float lastRin,f_k1,f_k2;
	static float perrRin;
	float result;

	f_k1 = f_k2 = 1.5;
//	if(target_in == 0)
//		result = 0;
//	else
		result=f_k1 * (target_in - lastRin)+ f_k2 * (target_in - 2 * lastRin + perrRin);

	perrRin = lastRin;
	lastRin= target_in;
	return result;
}

/**************************************************************************
函数功能：位置式PID控制器
入口参数：编码器测量位置信息，目标位置
返回  值：电机PWM
根据位置式离散PID公式
pid[0]:Kp
pid[1]:Ki
pid[2]:Kd
pwm=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
e(k)代表本次偏差
e(k-1)代表上一次的偏差
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,,k;
pwm代表输出
**************************************************************************/

int Position_PID(int position,int target)
{
	 static float Bias,Integral_bias,Last_Bias;
	 static int16_t Pwm;
	 Bias = target - position;                                  //计算偏差
	 Integral_bias += Bias;	                                 //求出偏差的积分

	 if(Integral_bias>3000)Integral_bias = 10000;				//限幅
	 if(Integral_bias<-3000)Integral_bias = -10000;

	 Pwm=pid[0] * Bias + pid[1] * Integral_bias + pid[2] * (Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias = Bias;                                       //保存上一次偏差
	 return Pwm;                                           //增量输出
}

float Position_PIDspeed(float position,float target)//编码器传参position，用户定义的速度传参target
{
	 static float Bias=0,Speed=0,Integral_bias=0,Last_Bias=0;
	 Bias=target-position;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 if(Integral_bias>3000)Integral_bias=3000;
	 if(Integral_bias<-3000)Integral_bias=-3000;
	 Speed=pid[0]*Bias+pid[1]*Integral_bias+pid[2]*(Bias-Last_Bias); //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差
	 return Speed;                                           //增量输出
}
