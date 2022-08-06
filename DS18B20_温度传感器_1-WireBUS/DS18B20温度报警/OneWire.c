#include <REGX52.H>

sbit OneWire_DQ = P3^7;

unsigned char OneWire_Init()		//单总线初始化
{
	unsigned char i;
	unsigned char AckBit;
	EA = 0;//关闭中断
	OneWire_DQ = 1;		 //初始化电平
	OneWire_DQ = 0;		 //拉低电平

	i = 247;while (--i); //延时500us

	OneWire_DQ = 1;		 //拉高电平

	i = 32;while (--i);  //延时70us

	AckBit = OneWire_DQ;

	i = 247;while (--i); //延时500us
	EA = 1;//打开中断
	return AckBit;
}
void OneWire_SendBit(unsigned char Bit)	   //发送一位
{
	unsigned char i;
	EA = 0;//关闭中断
	
	OneWire_DQ = 0;		 //拉低电平

	i = 4;while (--i);	 //延时10us
	OneWire_DQ = Bit;

	i = 24;while (--i);	 //延时50us
	OneWire_DQ = 1;		 //释放电平
	EA = 1;//打开中断
}
unsigned char OneWire_ReceiveBit()		//接收一位
{
	unsigned char i;
	unsigned char Bit;
	EA = 0;//关闭中断
	OneWire_DQ = 0;		 //拉低电平

	i = 2;while (--i);	 //延时5us
	OneWire_DQ = 1;		 //释放电平，此后电平变化由从机决定，

	i = 2;while (--i);	 //延时5us，进行采样，将采样结果赋给Bit
	Bit = OneWire_DQ;

	i = 24;while (--i);	 //延时50us
	EA = 1;//打开中断
	return Bit;

}

void OneWire_SendByte(unsigned char Byte)	  //发送一个字节
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		OneWire_SendBit(Byte&(0x01<<i));//Byte&(0x01<<i)将Byte的第3位发送出去（低位在前先发送）
	}
}
unsigned char OneWire_ReceiveByte()			 //接收一个字节
{
	unsigned char i;
	unsigned char Byte = 0x00;

	for(i=0;i<8;i++)
	{
		if(OneWire_ReceiveBit()){Byte|=(0x01<<i);};
	}

	return Byte;
}












