#include <REGX52.H>
#include "DELAY.H"
#include "KEY.H"
#include "TIMER0.H"
#include "NIXIE.H"

sbit Motor = P1^0;

unsigned char Counter;	  //可以理解为周期
unsigned char Compare[]={0,30,60,90};

unsigned char KeyNum,Speed;

void main()
{
	Timer0_Init();
	while(1)
	{
		KeyNum = Key();
		if(KeyNum == 1)
		{
			Speed++;
			Speed %=4;
		}
		Nixie(1,Speed);
	}
}
void Timer0_Routine() interrupt 1
{
	TL0 = 0x9C;		//设置定时初始值
	TH0 = 0xFF;		//设置定时初始值
	Counter++;
	if(Counter>=100)
	{
		Counter = 0;
	}
	// Counter %= 100;  可以实现if语句的功能
	if(Compare[Speed] > Counter)
	{
		Motor = 1;
	}
	else
	{
		Motor = 0;
	}
}