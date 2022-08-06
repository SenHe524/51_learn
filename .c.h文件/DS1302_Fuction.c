#include <REGX52.H>

sbit DS1302_SCLK = P3^6;
sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;
//写
#define DS1302_W_SEC   0x80	 
#define DS1302_W_MIN   0x82	 
#define DS1302_W_HOUR  0x84
#define DS1302_W_DATE  0x86
#define DS1302_W_MONTH 0x88
#define DS1302_W_YEAR  0x8C
#define DS1302_W_DAY   0x8A	 //星期
#define DS1302_W_WP    0x8E
//读
#define DS1302_R_SEC   0x81
#define DS1302_R_MIN   0x83
#define DS1302_R_HOUR  0x85
#define DS1302_R_DATE  0x87
#define DS1302_R_MONTH 0x89
#define DS1302_R_YEAR  0x8D
#define DS1302_R_DAY   0x8B

unsigned char DS1302_TIME[]={22,1,12,11,54,55,3}; //时间数组


void DS1302_Init()	  //初始化函数
{
	DS1302_CE = 0;
	DS1302_SCLK	= 0;
}
void DS1302_WriteByte(unsigned char Command,unsigned char Data)	   //DS1302写入函数
{
	unsigned char i;

	DS1302_CE = 1;

	for(i=0;i<8;i++)
	{
		DS1302_IO = Command&(0x01<<i);
		DS1302_SCLK = 1;//若单片机运行速度较快，需要加延时函数保证下一步置零成功
		DS1302_SCLK = 0;
	}
	for(i=0;i<8;i++)
	{
		DS1302_IO = Data&(0x01<<i);
		DS1302_SCLK = 1;//若单片机运行速度较快，需要加延时函数保证下一步置零成功
		DS1302_SCLK = 0;
	}
	DS1302_CE = 0;
}

char DS1302_ReadByte(unsigned char Command)		  //DS1302读取函数
{
	unsigned char i,Data = 0x00;

	DS1302_CE = 1;

	for(i=0;i<8;i++)
	{
		DS1302_IO = Command&(0x01<<i);
		DS1302_SCLK = 0;	   //此时DS1302_SCLK先零后一，参照DS1302读取时的时序图
		DS1302_SCLK = 1;	   //可知此时读取上升沿使能	
	}
	
	for(i=0;i<8;i++)
	{
		DS1302_SCLK = 1;	   //此时DS1302_SCLK先一后零，参照DS1302读取时的时序图
		DS1302_SCLK = 0;	   //可知此时读取下降沿使能
		if(DS1302_IO)
		{
			Data = Data|(0x01<<i);
		}
	}
	DS1302_IO = 0;
	DS1302_CE = 0;
	return Data;
}

void DS1302_SetTime()					 //设置时间函数
{
	DS1302_WriteByte(0x8E,0x00);  //解除写入保护
	DS1302_WriteByte(DS1302_W_YEAR,DS1302_TIME[0]/10*16+DS1302_TIME[0]%10);
	DS1302_WriteByte(DS1302_W_MONTH,DS1302_TIME[1]/10*16+DS1302_TIME[1]%10);
	DS1302_WriteByte(DS1302_W_DATE,DS1302_TIME[2]/10*16+DS1302_TIME[2]%10);
	DS1302_WriteByte(DS1302_W_HOUR,DS1302_TIME[3]/10*16+DS1302_TIME[3]%10);
	DS1302_WriteByte(DS1302_W_MIN,DS1302_TIME[4]/10*16+DS1302_TIME[4]%10);
	DS1302_WriteByte(DS1302_W_SEC,DS1302_TIME[5]/10*16+DS1302_TIME[5]%10);
	DS1302_WriteByte(DS1302_W_DAY,DS1302_TIME[6]/10*16+DS1302_TIME[6]%10);
	DS1302_WriteByte(0x8E,0x00);  //解除写入保护
}

void DS1302_ReadTime()			 ////将时间读取到DS1302_TIME数组中
{
	unsigned char Temp;
	
	Temp = DS1302_ReadByte(DS1302_R_YEAR);
	DS1302_TIME[0] = Temp /16*10+Temp%16;

	Temp = DS1302_ReadByte(DS1302_R_MONTH);
	DS1302_TIME[1] = Temp /16*10+Temp%16;

	Temp = DS1302_ReadByte(DS1302_R_DATE);
	DS1302_TIME[2] = Temp /16*10+Temp%16;

	Temp = DS1302_ReadByte(DS1302_R_HOUR);
	DS1302_TIME[3] = Temp /16*10+Temp%16;

	Temp = DS1302_ReadByte(DS1302_R_MIN);
	DS1302_TIME[4] = Temp /16*10+Temp%16;

	Temp = DS1302_ReadByte(DS1302_R_SEC);
	DS1302_TIME[5] = Temp /16*10+Temp%16;
	

}











