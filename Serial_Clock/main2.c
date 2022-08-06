#include <REGX52.H>
#include "UART.H"
#include "TIMER0.H"
#include "NIXIE_TIMER.H"
#include "MATRIX_TIMER.H"
//#include "KEY_TIMER.H"

unsigned char Con_Clock;	//时钟自走标志位
unsigned char ReceiveData;	//串口接收数据变量
unsigned char Hour=12,Min=35,Sec=10,Tim;	 //时间参数
unsigned char KeyNum,Flag;		 //接收键码

void Clock_Show();		 //时钟数码管显示函数
void Clock_Loop();		 //定时器调用时钟自走函数
void Clock_SetTime();	 //时钟设置函数

void main()
{
	UART_Init();
	Timer0_Init();

	UART_SendByte(0x35);

	while(1)
	{
		Clock_Show();		 //数码管显示时间
		if(ReceiveData == 'R')	   //判断串口接收数据是否为“R”  启动
		{
			Con_Clock = 1;		  //时间自走标志位置1，开启时钟
			Flag = 0;
		}
		else if(ReceiveData == 'P')	 //判断串口接收数据是否为“P”	  暂停
		{
			Con_Clock = 0;			  //时间自走标志位置0，暂停时钟
		}
		else if(ReceiveData == 'C')	  //判断串口接收数据是否为“C”	   更改
		{
			Con_Clock = 0;			 //时间自走标志位置0，暂停时钟
			Clock_SetTime();		 //调用时间设置函数
		}
		
	}
}
void UART_Routine() interrupt 4		 //串口中断
{
	if(RI)		 //若有数据 则进入
	{
		if((SBUF == 'R') || (SBUF == 'P') || (SBUF == 'C'))	   //过滤其他数据
		{
			ReceiveData = SBUF;
			RI = 0;
		}
		RI = 0;
	}
}

void Timer0_Routine() interrupt 1	  //定时器中断
{
	static unsigned int T0count1,T0count2,T0count3;//
	TL0 = 0x18;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	if(T0count1>=1000)	   //每1s调用一次Clock_Loop
	{
		T0count1 = 0;
		Clock_Loop();
		Tim++;
	}
	T0count1++;
	if((T0count2 >= 10) && (ReceiveData == 'C'))	  //每10ms调用一次Matrix_Loop
	{
		T0count2 = 0;
		Matrix_Loop();
	}
	T0count2++;
	if(T0count3 >= 2)		 //每2ms调用一次Nixie_Loop
	{
		T0count3 = 0;
		Nixie_Loop();
	}
	T0count3++;
}
void Clock_Loop()	   //时钟更新函数
{
	if(Con_Clock)
	{
		Sec++;
		if(Sec>=60)
		{
			Sec = 0;
			Min++;
			if(Min>=60)
			{
				Min = 0;
				Hour++;
				if(Hour>=24)
				{
					Hour = 0;
				}
			}
		}
	}	
}
void Clock_Show()		  //时间显示函数
{
	Nixie_Scan(3,17);	 //显示横杠
	Nixie_Scan(6,17);	
	if((Flag == 0) && (ReceiveData == 'C') && (Tim%2 == 0))
	{
		Nixie_Scan(7,16);
		Nixie_Scan(8,16);
	}
	else
	{
		Nixie_Scan(7,Sec/10);
		Nixie_Scan(8,Sec%10);
	}	
	if((Flag == 1) && (ReceiveData == 'C') && (Tim%2 == 0))
	{
		Nixie_Scan(4,16);
		Nixie_Scan(5,16);
	}
	else
	{
		Nixie_Scan(4,Min/10);
		Nixie_Scan(5,Min%10);
	}
	if((Flag == 2) && (ReceiveData == 'C') && (Tim%2 == 0))
	{
		Nixie_Scan(1,16);
		Nixie_Scan(2,16);
	}
	else
	{
		Nixie_Scan(1,Hour/10);
		Nixie_Scan(2,Hour%10);
	}
	if(ReceiveData != 'C')
	{
		Nixie_Scan(1,Hour/10);
		Nixie_Scan(2,Hour%10);
		Nixie_Scan(4,Min/10);
		Nixie_Scan(5,Min%10);
		Nixie_Scan(7,Sec/10);
		Nixie_Scan(8,Sec%10);	
	}
	Tim %=10 ;
}
void Clock_SetTime()		  //时钟设置函数
{
	KeyNum = Matrix_Num();
	if(KeyNum)
	{
//		UART_SendByte(0x35);
		if(KeyNum == 1)
		{
			Flag += 1;Flag %= 3;//Flag越界判断，若大于等于3，则赋值0；
		}
		else if((KeyNum == 2) && (Flag == 0))	  //按下键2，则进行  +
		{
			Sec++;
			Sec %= 60;
		}
		else if((KeyNum == 2) && (Flag == 1))
		{
			Min++;
			Min %= 60;
		}
		else if((KeyNum == 2) && (Flag == 2))
		{
			Hour++;
			Hour %= 24;
		}
		else if((KeyNum == 3) && (Flag == 0))	  //按下键3，则进行  -
		{
			if(Sec == 0){Sec = 60;}
			Sec--;	
		}
		else if((KeyNum == 3) && (Flag == 1))
		{
			if(Min == 0){Min = 60;}
			Min--;
		}
		else if((KeyNum == 3) && (Flag == 2))
		{
			if(Hour == 0){Hour = 24;}
			Hour--;
		}
	}	
}