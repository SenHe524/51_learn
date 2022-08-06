#include <REGX52.H>
#include <TIMER0.H>

void Timer0_Routine() interrupt 1
{
	static unsigned int T0count;
	TL0 = 0x18;		//���ö�ʱ��ʼֵ
	TH0 = 0xFC;		//���ö�ʱ��ʼֵ
	if(T0count>=500)
	{
		T0count = 0;
		P2_0 = ~P2_0;
	}
	T0count++;

}

void main()
{
	Timer0_Init();
	while(1)
	{
	}
}