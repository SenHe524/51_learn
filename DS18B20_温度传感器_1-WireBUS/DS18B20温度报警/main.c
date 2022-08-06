#include <REGX52.H>
#include "LCD1602.H"
#include "DS18B20.H"
#include "DELAY.H"
#include "AT24C02.H"
#include "KEY_TIMER.H"

float T,TShow;
char TL = 5,TH = 35;
unsigned char K_Num;

void main()
{
	LCD_Init();					  //LCD��ʼ��
	Timer0_Init();				  //��ʱ����ʼ��
	DS18B20_ConvertTemp();		  //�ϵ缴ת��һ���¶ȣ����Ǵ�ǰ������
	Delayms(1000);				  //��ʱ1s
	TH = AT24C02_ReadByte(0);	  //��ȡ��ֵ�¶�
	TL = AT24C02_ReadByte(1);
	if(TH>50||TL<-20||TH<TL)	   //�ж���ֵ�Ƿ�Ϸ��������Ϸ������ֵ
	{
		TH = 35;
		TL=5;
	}	
	LCD_ShowString(1,1,"T:");
	LCD_ShowString(2,1,"TH:");
	LCD_ShowString(2,9,"TL:");
	LCD_ShowSignedNum(2,4,TH,3);
	LCD_ShowSignedNum(2,12,TL,3);
	while(1)
	{
		K_Num = Key();
		/*�¶ȶ�ȡ����ʾ*/
		DS18B20_ConvertTemp();	  //ת���¶�
		T = DS18B20_Read_T();	  //��ȡ�¶�
		if(T<0)
		{
			LCD_ShowChar(1,3,'-');
			TShow = -T;
		}
		else
		{
			LCD_ShowChar(1,3,'+');
			TShow = T;
		}

		LCD_ShowNum(1,4,TShow,3);
		LCD_ShowChar(1,7,'.');
		LCD_ShowNum(1,8,(unsigned long)(TShow*100)%100,2);

		/*��ֵ�жϼ�ʾ��*/
		if(K_Num)
		{
			switch(K_Num)
			{
				case 1:
					TH++;if(TH>50){TH--;}
					break;
				case 2:
					TH--;if(TH<=TL){TH++;}
					break;
				case 3:
					TL++;if(TL>=TH){TL--;}
					break;
				case 4:
					TL--;if(TL<-50){TL++;}
					break;
				default:
					break;
			}
		}
		LCD_ShowSignedNum(2,4,TH,3);
		LCD_ShowSignedNum(2,12,TL,3);
		AT24C02_WriteByte(0,TH);
		Delayms(5);
		AT24C02_WriteByte(1,TL);
		Delayms(5);
		if(T>TH)
		{
			LCD_ShowString(1,13,"W:H");

		}
		else if(T<TH&&T>TL)
		{
			LCD_ShowString(1,13,"   ");
		}
		else if(T<TL)
		{
			LCD_ShowString(1,13,"W:L");
		}
	}
}
void Timer0_Routine() interrupt 1
{
	static unsigned int T0count;
	TL0 = 0x18;		//���ö�ʱ��ʼֵ
	TH0 = 0xFC;		//���ö�ʱ��ʼֵ
	if(T0count>=20)
	{
		T0count = 0;
		Key_Loop();
	}
	T0count++;

}