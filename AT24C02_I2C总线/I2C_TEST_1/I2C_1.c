#include <REGX52.H>
#include <string.h>
#include "LCD1602.H"
#include "KEY.H"
#include "AT24C02.H"
#include "I2C.H"
#include "DELAY.H"
#include "D_Scr.H"

void main()
{
	unsigned int Data = 0;

	LCD_Init();
//	LCD_ShowString(1,1,"Password:");
//    AT24C02_WriteByte(0,4);//经试验发现，两次写入之间必须延时，否则会写入错误
//	Delayms(5);
//	AT24C02_WriteByte(1,5);
//	Delayms(5);
//	AT24C02_WriteByte(55,8);//在写入之后，跟一个延时，再读取
//	Delayms(5);
//    Data = AT24C02_ReadByte(55);
//	if(Data==8)
//	{
//		D_Scr_Byte(1);	
//	}
//	else
//	{
//		D_Scr_Byte(2);	
//	}
	LCD_ShowNum(2,1,166,4);

//	while(1)
//	{
	
//	}
}