#include <REGX52.H>
#include "TIMER0.H"
#include "INTRINS.H"
#include "DELAY.H"
#include "KEY.H"
unsigned char KeyNum,LedMode;

void main()
{
	P2=0xFE;//��ʼ��LED��ʹ����һ����
	Timer0_Init();	  //��ʱ����ʼ��
	while(1)
	{
		KeyNum = Key();	//��ⰴ���Ƿ񱻰��£����µİ����Ǽ���
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
	TL0 = 0x18;		//���ö�ʱ��ʼֵ
	TH0 = 0xFC;		//���ö�ʱ��ʼֵ
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