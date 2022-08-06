#include <REGX52.H>

/*		B7   B6   B5   B4   B3   B2   B1   B0
scon :  SM0	 SM1  SM2  REN  TB8  TB9  TI   RI
		SM0与SM1控制串口工作方式，REN接收使能（置1时允许接收，置零时禁止接收），
		TI、RI分别为发送中断和接受中断，置1时发送或者接收中断完成
		由软件进行复位置零，此时可发送或接收数据；
*/

/**
   *	@brief	串口初始化	 //4800bps @12MHZ
   *	@param	无
   *	@retval	无
   */	
void UART_Init()			 
{
	SCON = 0x50;
	PCON = 0x80;
	TMOD &= 0x0F;	//清除定时器1模式位
	TMOD |= 0x20; 	//设置定时器1为8位自动重装模式
	TH1 = 0xF3;	   //设置定时初值  F3=243;256-243=13us;1/13us=0.0769230769230769MHZ
	TL1 = 0xF3;	   //设置定时重装值	   0.076923/16=0.004807MHZ  即4807bps
	TR1 = 1; 	   //启动定时器1
	EA = 1;
	ES = 1;
	
}

/**
   *	@brief	串口发送一个字节数据
   *	@param	Data:要发生的数据
   *	@retval	无
   */	
void UART_SendByte(unsigned char Data)
{
	SBUF = Data;
	while(!TI);
	TI = 0;
}