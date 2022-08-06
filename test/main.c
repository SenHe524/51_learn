#include <REGX52.H>
//#include "NIXIE.H"
#include "TIMER0.H"
#include "Matrix_TIMER.H"
#include "NIXIE_TIMER.H"


unsigned char KeyNum;

void main()
{
	Timer0_Init();
	while(1)
	{
		 KeyNum = Matrix_Num();
		 if(KeyNum)
		 Nixie_Scan(1,KeyNum);
	}
}
void Timer0_Routine() interrupt 1
{
	static unsigned int T0count1,T0count2;
	TL0 = 0x18;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	if(T0count1>=10)
	{
		T0count1 = 0;
		Matrix_Loop();
	}
	T0count1++;
	if(T0count2>=2)
	{
		T0count2 = 0;
		Nixie_Loop();
	}
	T0count2++;

}

