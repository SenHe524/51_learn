#include <REGX52.H>
#include "TIMER0.H"
#include "KEY_TIMER.H"
#include "NIXIE.H"
#include "DELAY.H"
#include "I2C.H"
#include "AT24C02.H"




unsigned char KeyNum,RunFlag;
unsigned char Min,Sec,MinSec;


void main()
{
	Timer0_Init();
	while(1)
	{
		KeyNum = Key();
		if(KeyNum)
		{
			if(KeyNum == 1)
			{
				RunFlag = !RunFlag;
			}
			else if(KeyNum == 2)
			{
				Min = 0;
				Sec = 0;
				MinSec = 0;
			}
			else if(KeyNum == 3)
			{
				AT24C02_WriteByte(0,Min);Delayms(5);
				AT24C02_WriteByte(1,Sec);Delayms(5);
				AT24C02_WriteByte(2,MinSec);Delayms(5);
			}
			else if(KeyNum == 4)
			{
				Min = AT24C02_ReadByte(0);
			    Sec = AT24C02_ReadByte(1);
				MinSec = AT24C02_ReadByte(2);
			}	
		}
		Nixie_Scan(1,Min/10);
		Nixie_Scan(2,Min%10);
		Nixie_Scan(3,17);
		Nixie_Scan(4,Sec/10);
		Nixie_Scan(5,Sec%10);
		Nixie_Scan(6,17);
		Nixie_Scan(7,MinSec/10);
		Nixie_Scan(8,MinSec%10);

	}
}
void Sec_Loop()
{
	if(RunFlag)
	{
		MinSec++;
		if(MinSec>=100)
		{
			MinSec = 0;
			Sec++;
			if(Sec>=60)
			{
				Sec = 0;
				Min++;
				if(Min>=60)
				{
					Min = 0;
				}
			}
		}
	}
}
void Timer0_Routine() interrupt 1
{
	static unsigned int T0count1,T0count2,T0count3;
	TL0 = 0x18;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	if(T0count1>=20)
	{
		T0count1 = 0;
		Key_Loop();
	}
	T0count1++;
	if(T0count2>=2)
	{
		T0count2 = 0;
		Nixie_Loop();
	}
	T0count2++;
	if(T0count3>=10)
	{
		T0count3 = 0;
		Sec_Loop();
	}
	T0count3++;
}