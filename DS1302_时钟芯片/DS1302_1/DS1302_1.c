#include <REGX52.H>
#include "DELAY.H"
#include "LCD1602.H"
#include "DS1302_FUCTION.H"

unsigned char Sec;

void main()
{
	LCD_Init();
	DS1302_Init();
	LCD_ShowString(1,3,"-");
	LCD_ShowString(1,6,"-");
	LCD_ShowString(2,3,"-");
	LCD_ShowString(2,6,"-");

	DS1302_SetTime();

	
	while(1)
	{
//		Sec = DS1302_ReadByte(0x81);  //读取DS1302的81H(秒)，并将其赋值给Sec
//		LCD_ShowNum(2,1,Sec/16*10+Sec%16,3);
		DS1302_ReadTime();
		LCD_ShowNum(1,1,DS1302_TIME[0],2);	
		LCD_ShowNum(1,4,DS1302_TIME[1],2);	
		LCD_ShowNum(1,7,DS1302_TIME[2],2);	
		LCD_ShowNum(2,1,DS1302_TIME[3],2);	
		LCD_ShowNum(2,4,DS1302_TIME[4],2);
		LCD_ShowNum(2,7,DS1302_TIME[5],2);	
	

	}
}