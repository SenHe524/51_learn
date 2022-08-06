#include <REGX52.H>
#include <TIMER0.H>
#include <DELAY.H>
#include <LCD1602.H>

unsigned int Hour=23,Min=59,Sec=50;	//ȫ�ֱ�����ֵΪ0��

void Timer0_Routine() interrupt 1
{
	static unsigned int T0count;
	TL0 = 0x18;		//���ö�ʱ��ʼֵ
	TH0 = 0xFC;		//���ö�ʱ��ʼֵ
	if(T0count>=1000)
	{
		T0count = 0;
		Sec++;
		if(Sec>=60)//Խ���жϣ���ʱ���λ��
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
	LCD_Init();//LCD��ʼ��
	Timer0_Init();//��ʱ����ʼ��
	LCD_ShowString(1,1,"Clock:");
	LCD_ShowString(2,1,"  :  :");
	while(1)
	{
		 LCD_ShowNum(2,1,Hour,2);//��ʾСʱ
		 LCD_ShowNum(2,4,Min,2);//��ʾ����
		 LCD_ShowNum(2,7,Sec,2);//��ʾ��
	}
}