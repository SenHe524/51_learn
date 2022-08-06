#include <REGX52.H>
#include "DELAY.H"
#include "KEY.H"
#include "TIMER0.H"

sbit DA = P2^1;

unsigned char Counter,Compare;	  

void main()
{
	unsigned char i;
	Timer0_Init();
	while(1)
	{
		for(i = 0; i < 100; i++)
		{
			Compare = i;
			Delayms(10);
		}
		for(i = 100; i > 0; i--)
		{
			Compare = i;
			Delayms(10);
		}	
	}
}
void Timer0_Routine() interrupt 1
{
	TL0 = 0x9C;		//���ö�ʱ��ʼֵ
	TH0 = 0xFF;		//���ö�ʱ��ʼֵ
	Counter++;
	if(Counter>=100)
	{
		Counter = 0;
	}
	// Counter %= 100;  ����ʵ��if���Ĺ���
	if(Compare > Counter)
	{
		DA = 1;
	}
	else
	{
		DA = 0;
	}
}