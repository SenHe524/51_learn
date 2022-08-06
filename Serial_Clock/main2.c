#include <REGX52.H>
#include "UART.H"
#include "TIMER0.H"
#include "NIXIE_TIMER.H"
#include "MATRIX_TIMER.H"
//#include "KEY_TIMER.H"

unsigned char Con_Clock;	//ʱ�����߱�־λ
unsigned char ReceiveData;	//���ڽ������ݱ���
unsigned char Hour=12,Min=35,Sec=10,Tim;	 //ʱ�����
unsigned char KeyNum,Flag;		 //���ռ���

void Clock_Show();		 //ʱ���������ʾ����
void Clock_Loop();		 //��ʱ������ʱ�����ߺ���
void Clock_SetTime();	 //ʱ�����ú���

void main()
{
	UART_Init();
	Timer0_Init();

	UART_SendByte(0x35);

	while(1)
	{
		Clock_Show();		 //�������ʾʱ��
		if(ReceiveData == 'R')	   //�жϴ��ڽ��������Ƿ�Ϊ��R��  ����
		{
			Con_Clock = 1;		  //ʱ�����߱�־λ��1������ʱ��
			Flag = 0;
		}
		else if(ReceiveData == 'P')	 //�жϴ��ڽ��������Ƿ�Ϊ��P��	  ��ͣ
		{
			Con_Clock = 0;			  //ʱ�����߱�־λ��0����ͣʱ��
		}
		else if(ReceiveData == 'C')	  //�жϴ��ڽ��������Ƿ�Ϊ��C��	   ����
		{
			Con_Clock = 0;			 //ʱ�����߱�־λ��0����ͣʱ��
			Clock_SetTime();		 //����ʱ�����ú���
		}
		
	}
}
void UART_Routine() interrupt 4		 //�����ж�
{
	if(RI)		 //�������� �����
	{
		if((SBUF == 'R') || (SBUF == 'P') || (SBUF == 'C'))	   //������������
		{
			ReceiveData = SBUF;
			RI = 0;
		}
		RI = 0;
	}
}

void Timer0_Routine() interrupt 1	  //��ʱ���ж�
{
	static unsigned int T0count1,T0count2,T0count3;//
	TL0 = 0x18;		//���ö�ʱ��ʼֵ
	TH0 = 0xFC;		//���ö�ʱ��ʼֵ
	if(T0count1>=1000)	   //ÿ1s����һ��Clock_Loop
	{
		T0count1 = 0;
		Clock_Loop();
		Tim++;
	}
	T0count1++;
	if((T0count2 >= 10) && (ReceiveData == 'C'))	  //ÿ10ms����һ��Matrix_Loop
	{
		T0count2 = 0;
		Matrix_Loop();
	}
	T0count2++;
	if(T0count3 >= 2)		 //ÿ2ms����һ��Nixie_Loop
	{
		T0count3 = 0;
		Nixie_Loop();
	}
	T0count3++;
}
void Clock_Loop()	   //ʱ�Ӹ��º���
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
void Clock_Show()		  //ʱ����ʾ����
{
	Nixie_Scan(3,17);	 //��ʾ���
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
void Clock_SetTime()		  //ʱ�����ú���
{
	KeyNum = Matrix_Num();
	if(KeyNum)
	{
//		UART_SendByte(0x35);
		if(KeyNum == 1)
		{
			Flag += 1;Flag %= 3;//FlagԽ���жϣ������ڵ���3����ֵ0��
		}
		else if((KeyNum == 2) && (Flag == 0))	  //���¼�2�������  +
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
		else if((KeyNum == 3) && (Flag == 0))	  //���¼�3�������  -
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