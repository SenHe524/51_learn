#include <REGX52.H>
#include "LCD1602.H"
#include "DELAY.H"
#include "XPT2046.H"

unsigned int AD_Value = 0;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"ADJ NTC RG");
	while(1)
	{
		AD_Value = XPT2046_ReadAD(XPT2046_XP_8);
		LCD_ShowNum(2,1,AD_Value,3);
		AD_Value = XPT2046_ReadAD(XPT2046_YP_8);
		LCD_ShowNum(2,5,AD_Value,3);
		AD_Value = XPT2046_ReadAD(XPT2046_VBAT_8);
		LCD_ShowNum(2,9,AD_Value,3);
		Delayms(10);
	}
}