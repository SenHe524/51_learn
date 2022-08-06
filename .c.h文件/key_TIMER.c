#include <REGX52.H>
#include "DELAY.H"

unsigned char K_KeyNumber;


/**
   *	@brief	获取按键键码
   *	@param	无
   *	@retval	按下的按键键码，范围;0-4,0表示无按键按下
   */
unsigned char Key()
{
	unsigned char Temp = 0;
	Temp = K_KeyNumber;
	K_KeyNumber = 0;
	return Temp;
}
/**
   *	@brief	获取当前按键的状态，无消抖及松手检测
   *	@param	无
   *	@retval	按下的按键的键码，范围;0-4,0表示无按键按下
   */
unsigned char Key_GetState()
{
	unsigned char KeyNumber = 0;
	if(P3_1==0){KeyNumber=1;}
	if(P3_0==0){KeyNumber=2;}
	if(P3_2==0){KeyNumber=3;}
	if(P3_3==0){KeyNumber=4;}
	return KeyNumber;
}


/**
   *	@brief	按键驱动函数，在中断中调用
   *	@param	无
   *	@retval	无
   */
void Key_Loop()
{
	static unsigned char N_State,L_State;
	unsigned int i;
	L_State	= N_State;	  //按键状态更新
	N_State = Key_GetState();		 //获取当前按键状态
	//若上一个中断按键按下，现在这个中断未按下，则判断为刚松手以此作为松手检测	
	for(i=0;i<4;i++)
	{
		if(L_State==(i+1) && N_State==0)
		{
			K_KeyNumber = i+1;
			break;
		}	
	}
}