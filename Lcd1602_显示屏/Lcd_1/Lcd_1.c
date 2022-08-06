#include <REGX52.H>
#include <TIMER0.H>
#include <DELAY.H>
#include <LCD1602.H>

unsigned int Hour=23,Min=59,Sec=50;	//全局变量初值为0；

void Timer0_Routine() interrupt 1
{
	static unsigned int T0count;
	TL0 = 0x18;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	if(T0count>=1000)
	{
		T0count = 0;
		Sec++;
		if(Sec>=60)//越界判断，即时间进位；
		{
			Sec=0;
			Min++;
			if(Min>=60)
			{
				Min=0;
				Hour++;
				if(Hour>=24)
				{
					Hour=0;
				}
			}
		}
	}
	T0count++;

}

void main()
{
	LCD_Init();//LCD初始化
	Timer0_Init();//定时器初始化
	LCD_ShowString(1,1,"Clock:");
	LCD_ShowString(2,1,"  :  :");
	while(1)
	{
		 LCD_ShowNum(2,1,Hour,2);//显示小时
		 LCD_ShowNum(2,4,Min,2);//显示分钟
		 LCD_ShowNum(2,7,Sec,2);//显示秒
	}
}