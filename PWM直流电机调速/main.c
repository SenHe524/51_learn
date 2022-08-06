#include <REGX52.H>
#include "DELAY.H"
#include "KEY.H"
#include "TIMER0.H"
#include "NIXIE.H"

sbit Motor = P1^0;

unsigned char Counter;	  //�������Ϊ����
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
	TL0 = 0x9C;		//���ö�ʱ��ʼֵ
	TH0 = 0xFF;		//���ö�ʱ��ʼֵ
	Counter++;
	if(Counter>=100)
	{
		Counter = 0;
	}
	// Counter %= 100;  ����ʵ��if���Ĺ���
	if(Compare[Speed] > Counter)
	{
		Motor = 1;
	}
	else
	{
		Motor = 0;
	}
}