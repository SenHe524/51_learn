#include <REGX52.H>
#include "TIMER0.H"
#include "KEY.H"
#include "NIXIE.H"

unsigned char KeyNum;
unsigned int i;
void main()
{
	Timer0_Init();
	P2_7 = 0;	   //1111 1111 & 1111 1110 = 1111 1110 
	while(1)
	{
		KeyNum = Key();
		if(KeyNum)
		{
			P2_7 = ~P2_7;
		}

	}
}
void Timer0_Routine() interrupt 1
{
	static unsigned int T0count1,T0count2;
	TL0 = 0x18;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	if(T0count1>=20)
	{
		T0count1 = 0;
		Key_Loop();
	}
	T0count1++;
	if(T0count2>=10)
	{
		T0count2 = 0;
		Nixie(1,0);
	}
	T0count2++;

}