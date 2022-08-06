#include <REGX52.H>
#include "DELAY.H"
#include "UART.H"
unsigned char code Table[] = {'1','2','3'};
unsigned char ReceiveData;

void UART_Routine() interrupt 4
{
	ReceiveData = UART_ReceiveByte();
//	if(RI){
//		ReceiveData = SBUF;
//		RI = 0;
//	}	
}
void main()
{
	UART_Init();
	while(1)
	{
		if(ReceiveData == Table[0])
		{
			P2 = 0xFE;
		}
		else if(ReceiveData == Table[1])
		{
			P2 = 0xFD;
		}
		else if(ReceiveData == Table[2])
		{
			P2 = 0xFC;
		}
		else if(ReceiveData == '0')
		{
			P2 = 0xFB;
		}
		else
		{
			P2 = 0x00;
			UART_SendByte(5+'0');
			Delayms(80);
		}
	}
}
