#include <REGX52.H>

unsigned char Matrix_Number;

unsigned char Matrix_Num()
{
	unsigned char Temp = 0;
	Temp = Matrix_Number;
	Matrix_Number = 0;
	return Temp;
}

/**
   *	@brief	获取矩阵按键的键码
   *	@param	无
   *	@retval	按下的矩阵按键的键码
   */
unsigned char Matrix_State()
{
	unsigned char KeyNumber = 99;
	P1 = 0xFF;P1_3 = 0;	   //依次检测矩阵键盘第一列的行是否导通
	if(P1_7==0){KeyNumber=1;}if(P1_6==0){KeyNumber=5;}
	if(P1_5==0){KeyNumber=9;}if(P1_4==0){KeyNumber=13;}

	P1 = 0xFF;P1_2 = 0;	   //依次检测矩阵键盘第二列的行是否导通
	if(P1_7==0){;KeyNumber=2;}if(P1_6==0){KeyNumber=6;}
	if(P1_5==0){KeyNumber=10;}if(P1_4==0){KeyNumber=14;}

	P1 = 0xFF;P1_1 = 0;	   //依次检测矩阵键盘第三列的行是否导通
	if(P1_7==0){KeyNumber=3;}if(P1_6==0){KeyNumber=7;}
	if(P1_5==0){KeyNumber=11;}if(P1_4==0){KeyNumber=15;}
	
	P1 = 0xFF;P1_0 = 0;	   //依次检测矩阵键盘第四列的行是否导通
	if(P1_7==0){KeyNumber=4;}if(P1_6==0){KeyNumber=8;}
	if(P1_5==0){KeyNumber=12;}if(P1_4==0){KeyNumber=16;}

	return KeyNumber;
}
void Matrix_Loop()
{
	static unsigned char N_State,L_State;
	unsigned int i;
	L_State	= N_State;	  //按键状态更新
	N_State = Matrix_State();		  //获取当前按键状态
	//若上一个中断按键按下，现在这个中断未按下，则判断为刚松手以此作为松手检测
	for(i=0;i<16;i++)
	{
		if(L_State==(i+1) && N_State==99)
		{
			Matrix_Number = i+1;
			break;
		}	
	}
}