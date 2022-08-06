#include <REGX52.H>
#include "DELAY.H"

/**
   *	@brief	获取矩阵按键的键码
   *	@param	无
   *	@retval	按下的矩阵按键的键码
   */
unsigned char Matrix_Num()
{
	unsigned char KeyNumber = 99;
	P1 = 0xFF;
	P1_3 = 0;
	if(P1_7==0){Delayms(20);while(P1_7==0);Delayms(20);KeyNumber=7;}
	if(P1_6==0){Delayms(20);while(P1_6==0);Delayms(20);KeyNumber=4;}
	if(P1_5==0){Delayms(20);while(P1_5==0);Delayms(20);KeyNumber=1;}
	if(P1_4==0){Delayms(20);while(P1_4==0);Delayms(20);KeyNumber=0;}

	P1 = 0xFF;
	P1_2 = 0;
	if(P1_7==0){Delayms(20);while(P1_7==0);Delayms(20);KeyNumber=8;}
	if(P1_6==0){Delayms(20);while(P1_6==0);Delayms(20);KeyNumber=5;}
	if(P1_5==0){Delayms(20);while(P1_5==0);Delayms(20);KeyNumber=2;}
	if(P1_4==0){Delayms(20);while(P1_4==0);Delayms(20);KeyNumber='C';}

	P1 = 0xFF;
	P1_1 = 0;
	if(P1_7==0){Delayms(20);while(P1_7==0);Delayms(20);KeyNumber=9;}
	if(P1_6==0){Delayms(20);while(P1_6==0);Delayms(20);KeyNumber=6;}
	if(P1_5==0){Delayms(20);while(P1_5==0);Delayms(20);KeyNumber=3;}
	if(P1_4==0){Delayms(20);while(P1_4==0);Delayms(20);KeyNumber='=';}
	
	P1 = 0xFF;
	P1_0 = 0;
	if(P1_7==0){Delayms(20);while(P1_7==0);Delayms(20);KeyNumber='+';}
	if(P1_6==0){Delayms(20);while(P1_6==0);Delayms(20);KeyNumber='-';}
	if(P1_5==0){Delayms(20);while(P1_5==0);Delayms(20);KeyNumber='*';}
	if(P1_4==0){Delayms(20);while(P1_4==0);Delayms(20);KeyNumber='/';}



	return KeyNumber;
}