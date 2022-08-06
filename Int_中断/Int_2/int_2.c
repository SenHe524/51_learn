#include <REGX52.H>
#include "TIMER0.H"
#include "INTRINS.H"
#include "DELAY.H"
#include "KEY.H"
unsigned char KeyNum,LedMode;

void main()
{
	P2=0xFE;//初始化LED，使其亮一个灯
	Timer0_Init();	  //定时器初始化
	while(1)
	{
		KeyNum = Key();	//检测按键是否被按下，按下的按键是几；
		if(KeyNum)
		{
			if(KeyNum == 1)
			{
				LedMode++;
				if(LedMode>=2)
				{
					LedMode = 0;
				}
			}
		}
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0count;
	TL0 = 0x18;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	if(T0count>=500)
	{
		T0count = 0;
		if(LedMode==0)
		{
			P2 = _crol_(P2,1);
		}
		if(LedMode==1)
		{
			P2 = _cror_(P2,1);
		}
	}
	T0count++;

}