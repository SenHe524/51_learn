#include <REGX52.H>
#include "DELAY.H"

sbit SER = P3^4;  //SER
sbit SCK = P3^6;  //SRCLK
sbit RCK = P3^5;  //RCLK

#define D_Scr_Port P0		//将P0口重命名位D_Scr_Port

/**
   *	@brief	点阵屏初始化
   *	@param	无
   *	@retval	无
   */	
void D_Scr_Init()
{
	SCK = 0;
    RCK = 0;
}

/**
   *	@brief	74HC595写入一个字节
   *	@param	Byte:要写入的字节
   *	@retval	无
   */	
void WriteByte_74595(unsigned char Byte)
{
	unsigned int i;
	//16进制Byte赋值给位SER，Byte非0，SER即1
	//Byte&1000 0000,Byte最高位为1,SER为1(1000 0000为非零)
	//Byte最高位为0,SER为0(0000 0000为0)
	for(i=0;i<8;i++)
	{
		SER = Byte&(0x80>>i);//0x80>>i   0x80位右移i位  
	    SCK = 1;//高电平移位
	    SCK = 0;//低电平,为下一次高电平做准备
	}
	RCK = 1;
	RCK = 0;				 
}

/**
   *	@brief	 LED点阵屏显示一列数据
   *	@param	 line:显示数据的列，范围：0~7，0为点阵屏最左列，7为最右列
   *	@param	 Data:需要显示的数据，高位在上，1亮，0灭
   *	@retval	 无
   */	
void D_Scr_Show(unsigned char line,unsigned char Data)
{
	WriteByte_74595(Data);
	D_Scr_Port = ~(0x80>>line); //将第line列的P0口为低电平，使其导通，即使LED能点亮
	Delayms(1);	//延时
	D_Scr_Port = 0xFF;	//位清零
}
