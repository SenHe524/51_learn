#include <REGX52.H>
#include "TIMER1.H"

sbit Motor = P1^0;

unsigned char Counter,Compare;	  //可以理解为周期

/**
  * @brief      电机初始化
  * @param  	无
  * @retval 	无
  */
void Motor_Init()
{
	Timer1_Init();
}
/**
  * @brief      电机速度设置
  * @param  	 Speed：0-100；
  * @retval 	 无
  */
void Motor_SetSpeed(unsigned char Speed)
{
	Compare = Speed;
}
/**
  * @brief      定时器1中断，实现PWM
  * @param  
  * @retval 
  */
void Timer1_Routine() interrupt 3
{
	TL1 = 0x9C;		//设置定时初始值
	TH1 = 0xFF;		//设置定时初始值
	Counter++;
	if(Counter>=100)
	{
		Counter = 0;
	}
	// Counter %= 100;  可以实现if语句的功能
	if(Compare > Counter)
	{
		Motor = 1;
	}
	else
	{
		Motor = 0;
	}
}