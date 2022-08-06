#include <REGX52.H>
#include "LCD1602.H"
#include "DS18B20.H"
#include "DELAY.H"


unsigned char Ack;

float T;

void main()
{
	DS18B20_ConvertTemp();
	Delayms(1000);
	LCD_Init();
	LCD_ShowString(1,1,"Temperature");

	while(1)
	{
		DS18B20_ConvertTemp();

		T = DS18B20_Read_T();
		if(T<0)
		{
			LCD_ShowChar(2,1,'-');
			T = -T;
		}
		else
		{
			LCD_ShowChar(2,1,'+');
		}

		LCD_ShowNum(2,2,T,3);
		LCD_ShowChar(2,5,'.');
		LCD_ShowNum(2,6,(unsigned long)(T*10000)%10000,4);

	}
}