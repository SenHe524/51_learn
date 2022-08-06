#include <REGX52.H>
#include <stdlib.h>
#include "TIMER0.H"
#include "MATRIX_NUM.H"
#include "DELAY.H"
#include "SHOW_74HC595.H"

unsigned char i;
unsigned char KeyNum,Game_State;  //�������룬��Ϸ״̬
unsigned char code Led[] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
unsigned char Snake_head[2];		      //��ͷλ��
unsigned char Snake_BodyColumn[30];	  //����λ�ã���
unsigned char Snake_BodyLine[30];	  //����λ�ã���
unsigned char Snake_Flag;   //������
unsigned char Temp_BodyColumn,Temp_BodyLine;	  //��ʱ�洢λ��
unsigned char Food_Line,Food_Column;   //ʳ������
unsigned char L_KeyNum;   	  //�洢ÿ��while��ɨ�赽�Ĳ�Ϊ���KeyNum

void Snake_Init();
void Food_Update();
void Snake_Show();
void Snake_Update();
void Snake_Move();
void Food_Touch();

void main()
{
	Timer0_Init(); //��ʱ����ʼ��
	D_Scr_Init();
	while(1)
	{
		KeyNum = Matrix_Num();	  //��ȡ����

		if((KeyNum == 6) && (Game_State == 0))//����Ϸδ��ʼʱ����6��ʼ��Ϸ
		{
			Game_State = 1;			//������Ϸ״̬
			Food_Column = rand()%8;	 //ʳ���ʼ��
			Food_Line = rand()%8;
			Snake_Init();			 //�����ݳ�ʼ��
			while(Game_State)		 //��Ϸѭ��
			{
				KeyNum = Matrix_Num();
				if(KeyNum != 0)	//���˰�������ʱMatrix_Num���ص�0
				{
					L_KeyNum = KeyNum;	 //���������븳ֵ��L_KeyNum
				}
				Food_Update();   //ʳ�����
				Snake_Show();	 //LED��ʾ��
				Food_Touch();	 //���ʳ����ײ
			}
		}
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0count1,T0count2;  
	TL0 = 0x18;		//���ö�ʱ��ʼֵ
	TH0 = 0xFC;		//���ö�ʱ��ʼֵ
	if(T0count1>=10)  //T0count1��ʱ����10ʱ����
	{
		T0count1 = 0;
		Matrix_Loop(); //��ʱ10ms�����һ�ΰ������
	}
	T0count1++;     //T0count1��ʱ��һ
	if(Game_State == 1) 
	{
		if(Snake_Flag<4)
		{
			if(T0count2 >= 700)   //T0count2��ʱ����700ʱ����
			{
				T0count2 = 0;
				Snake_Move(); 	 //ÿ700ms���ƶ�һ��
			}	
	 		T0count2++;	   //T0count1��ʱ��һ
		}
		else if((Snake_Flag < 7) && (Snake_Flag >= 4))
		{
			if(T0count2 >= 500)   //T0count2��ʱ����500ʱ����
			{
				T0count2 = 0;
				Snake_Move(); 	 //ÿ500ms���ƶ�һ��
			}	
	 		T0count2++;	   //T0count1��ʱ��һ
		}
		else
		{
			if(T0count2 >= 300)   //T0count2��ʱ����300ʱ����
			{
				T0count2 = 0;
				Snake_Move(); 	 //ÿ300ms���ƶ�һ��
			}	
	 		T0count2++;	   //T0count1��ʱ��һ
		}
		
	}
}

void Snake_Init()
{
	Snake_head[0] = 2;Snake_head[1] = 0;	 //��ͷ��ʼλ�ã�1������
	Snake_BodyColumn[0] = 1;
	Snake_BodyColumn[1] = 0;	  //�����ʼλ�ã���
	Snake_BodyLine[0] = 0;
	Snake_BodyLine[1] = 0;	  //�����ʼλ�ã���
	Snake_Flag = 2;
	L_KeyNum = 0;
	Temp_BodyColumn,Temp_BodyLine;	  //��ʱ�洢λ��
}
void Food_Update()
{
	unsigned char j;
	if((Snake_head[0] == Food_Column) && (Snake_head[1] == Food_Line)) 
	{
		Food_Column = rand()%8;	  //�ж���ͷ��ʳ���غ�ʱ������ʳ��λ��
		Food_Line = rand()%8;

	}
	for(j=0;j<Snake_Flag;j++)
	{
		if((Snake_BodyColumn[j] == Food_Column) 
		&& (Snake_BodyLine[j] == Food_Line))
		{
			Food_Column = rand()%8;	  //�ж�������ʳ���غ�ʱ������ʳ��λ��
			Food_Line = rand()%8;
		}
	}
}
void Snake_Show()	  //LED��ʾ�ߵ�������ͷ��ʳ��
{
	for(i=0;i<Snake_Flag;i++)
	{
		D_Scr_Show(Snake_BodyColumn[i],Led[Snake_BodyLine[i]]);
	}
	D_Scr_Show(Snake_head[0],Led[Snake_head[1]]);
	D_Scr_Show(Food_Column,Led[Food_Line]);
}
void Snake_Update()		  
{
	for(i = 0; i < Snake_Flag; i++)		  //���������ײ
	{
		if((Snake_head[0] == Snake_BodyColumn[i]) && (Snake_head[1] == Snake_BodyLine[i]))
		{
			Game_State = 0;			//��ͷ����ײ������Ϸ����
			break;
		}
	}
	Temp_BodyColumn = Snake_head[0];   //��¼��ͷ������
	Temp_BodyLine = Snake_head[1];
	for(i=0;i<Snake_Flag-1;i++)		   //ѭ����������
	{
		Snake_BodyColumn[Snake_Flag-1-i]=Snake_BodyColumn[Snake_Flag-i-2];
		Snake_BodyLine[Snake_Flag-1-i]=Snake_BodyLine[Snake_Flag-i-2];
	}
	Snake_BodyColumn[0] = Temp_BodyColumn;
	Snake_BodyLine[0] = Temp_BodyLine;

}

void Snake_Move()
{
	if(L_KeyNum == 2)       //��������Ϊ2ʱ����������
	{
		Snake_Update();	  //�����߸��º���
		if(Snake_head[1] == 0)		//��ͷ�������
		{
			Snake_head[1] = 7;	   //����ͷ����������·�����
		}
		else
		{
			Snake_head[1] -= 1;	  //��δ��������ͷ������������λ
		}
	}
	else if(L_KeyNum == 5)  //��������Ϊ5ʱ����������
	{
		Snake_Update();	  //�����߸��º���
		if(Snake_head[0] == 0)
		{
			Snake_head[0] = 7;	 //����ͷ������������ҷ�����
		}
		else
		{
			Snake_head[0] -= 1;	  //������ͷ������������λ
		}
	}
	else if(L_KeyNum == 7)  //��������Ϊ7ʱ����������
	{
		Snake_Update();	  //�����߸��º���
		if(Snake_head[0] == 7)
		{
			Snake_head[0] = 0;	  //����ͷ�����ҷ�������󷽳���
		}
		else
		{
			Snake_head[0] += 1;	  //������ͷ������������λ
		}
	}
	else if(L_KeyNum == 10) //��������Ϊ10ʱ����������
	{
		Snake_Update();
		if(Snake_head[1] == 7)		//��ͷ���׼��
		{
			Snake_head[1] = 0;	   //����ͷ����������Ϸ�����
		}
		else
		{
			Snake_head[1] += 1;	   //������ͷ������������λ
		}
	}
	else if(L_KeyNum == 1)		 //����Ϊ1ʱ��ֹͣ��Ϸ
	{
		Game_State = 0;
	}

}
void Food_Touch()
{						 
	if((Snake_head[0] == Food_Column) && (Snake_head[1] == Food_Line))
	{
		if(Snake_Flag<10)
		{
			Snake_Flag += 1;	   //��ͷ������ʳ��ʱ�������ȼ�1��
			//����β���и�ֵ�������Ŀհ�����
			Snake_BodyColumn[Snake_Flag-1] = Snake_BodyColumn[Snake_Flag-2];
			Snake_BodyLine[Snake_Flag-1] = Snake_BodyLine[Snake_Flag-2];
		}
//		else
//		{
//			D_Scr_Byte(1);
//			Game_State = 0;
//		}
	}
}
