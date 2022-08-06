#include <REGX52.H>
#include "LCD1602.H"
#include "MATRIX_NUM.H"


unsigned char K_Num,Sym[4];//K_Num ���󰴼����룬Sym ��+ - * /��
unsigned long Data_1,Data_2,Data_3;//Data_1:��һ������  Data_2:�ڶ�������  Data_3�����

unsigned char CFlag_1,CFlag_2;  //CFlag_1���Ƿ��¼Ӽ��˳��ı�־λ  CFlag_2���Ƿ��µȺŵı�־λ
unsigned int i,Num[8];
unsigned long Pow(int X,int Y);

void main()
{
	
	LCD_Init();
	LCD_ShowString(1,1,"OK!");
	while(1)
	{
		K_Num = Matrix_Num();//��ȡ����
		if(K_Num != 99)//�����������
		{			
			if((K_Num != '+') && (K_Num != '-') && (K_Num != '*')
				&& (K_Num != 'C') && (K_Num != '=') && (K_Num != '/')
				&& (CFlag_1 == 0) && (CFlag_2 == 0))//��һ�����ݵ������ж�
			{					
				if(Data_1 < 1000)//�������������λ��
				{
					Data_1 *= 10;
					Data_1 += K_Num;
					LCD_ShowNum(1,1,Data_1,4); 	//��ʾ����			
				}
			}
			else if(((K_Num == '+') || (K_Num == '-') || (K_Num == '*') //+ - * /�ļ��
				|| (K_Num == '/')) && (CFlag_2 == 0))
			{						 
				CFlag_1 = 1;
				Sym[0] = K_Num;
				LCD_ShowString(1,6,Sym);
			}
			else if((K_Num != '+') && (K_Num != '-') && (K_Num != '*')
				&& (K_Num != 'C') && (K_Num != '=') && (K_Num != '/')
				&& (CFlag_1 == 1) && (CFlag_2 == 0))//�ڶ������ݵ������ж�
			{
				if(Data_2 <= 1000)//
				{
					Data_2 *= 10;
					Data_2 += K_Num;
					LCD_ShowNum(1,8,Data_2,4);
				}  
			}
			else if((K_Num == '=') && (CFlag_1 == 1) && (CFlag_2 == 0))//�Ⱥ��жϣ����µȺż���������
			{
				LCD_ShowString(1,14,"=");
				if(Sym[0] == '+')
				{
					Data_3 = Data_1+Data_2;
				}
				else if(Sym[0] == '-')
				{
					Data_3 = Data_1-Data_2;
				}
				else if(Sym[0] == '*')
				{
					Data_3 = Data_1*Data_2;
				}
				else if(Sym[0] == '/')
				{
					Data_3 = Data_1/Data_2;
				}
				CFlag_2 = 1;  //���µȺź�����ǰ�����ڣ�������ı�Data_1 Data_2 Sym
				for(i=0;i<8;i++)
				{
					Num[i] = (Data_3/Pow(10,7-i))%10;
				}
				for(i=0;i<8;i++)
				{
					LCD_ShowNum(2,7+i,Num[i],1);
				}//��ʾ Data_3
			}
			else if(K_Num == 'C')  //������Ӧ����C֮���ʼ��
			{
				Data_1 = 0;
				Data_2 = 0;
				Data_3 = 0;
				CFlag_1 = 0;
				CFlag_2 = 0;
				for(i=0;i<8;i++)
				{
					Num[i] = 0;
				}
				LCD_ShowNum(1,1,Data_1,4);
				LCD_ShowNum(1,8,Data_2,4);
				LCD_ShowString(1,6," ");
				LCD_ShowString(2,6,"            ");
			}

		} 
	}
}
unsigned long Pow(int X,int Y)
{
	unsigned char i;
	unsigned long Result=1;
	for(i=0;i<Y;i++)
	{
		Result*=X;
	}
	return Result;
}