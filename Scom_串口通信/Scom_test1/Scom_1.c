#include <REGX52.H>

typedef unsigned int uint;
typedef unsigned char uchar;
const char table[8]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,
0x7F};

void Scom_Init()	 //初始化串口,波特率：4800，倍频；
{
	TMOD = 0x20;//0010 0000
	TH1 = 0xF3;
	TL1 = 0xF3;
	PCON = 0x80;//1000 0000
	TR1= 1;
	SCON = 0x50;//0101 0000
	ES = 1;
	EA = 1;
}

void Usart() interrupt 4	  //串口中断
{
    uchar receiveData;
	receiveData = SBUF;  //定义一个变量 存储 数据缓冲器SBUF中的数据；
	RI = 0;	  //RI接受中断标志位，置零时可接收数据
	SBUF = receiveData;	   //将数据存放进数据缓冲器SBUF；
	while(!TI);  //发送时：TI为0，发送完成后：TI为1，此时!TI为0，跳出while；
	TI = 0;	  //TI发送中断标志位，置零时可发送数据
}
	 

void main()
{
	Scom_Init();
	while(1);
}