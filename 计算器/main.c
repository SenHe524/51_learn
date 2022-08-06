#include <REGX52.H>
#include "LCD1602.H"
#include "MATRIX_NUM.H"


unsigned char K_Num,Sym[4];//K_Num 矩阵按键键码，Sym “+ - * /”
unsigned long Data_1,Data_2,Data_3;//Data_1:第一个数据  Data_2:第二个数据  Data_3：结果

unsigned char CFlag_1,CFlag_2;  //CFlag_1：是否按下加减乘除的标志位  CFlag_2：是否按下等号的标志位
unsigned int i,Num[8];
unsigned long Pow(int X,int Y);

void main()
{
	
	LCD_Init();
	LCD_ShowString(1,1,"OK!");
	while(1)
	{
		K_Num = Matrix_Num();//获取键码
		if(K_Num != 99)//如果按键按下
		{			
			if((K_Num != '+') && (K_Num != '-') && (K_Num != '*')
				&& (K_Num != 'C') && (K_Num != '=') && (K_Num != '/')
				&& (CFlag_1 == 0) && (CFlag_2 == 0))//第一个数据的输入判断
			{					
				if(Data_1 < 1000)//限制数据最大四位数
				{
					Data_1 *= 10;
					Data_1 += K_Num;
					LCD_ShowNum(1,1,Data_1,4); 	//显示出来			
				}
			}
			else if(((K_Num == '+') || (K_Num == '-') || (K_Num == '*') //+ - * /的检测
				|| (K_Num == '/')) && (CFlag_2 == 0))
			{						 
				CFlag_1 = 1;
				Sym[0] = K_Num;
				LCD_ShowString(1,6,Sym);
			}
			else if((K_Num != '+') && (K_Num != '-') && (K_Num != '*')
				&& (K_Num != 'C') && (K_Num != '=') && (K_Num != '/')
				&& (CFlag_1 == 1) && (CFlag_2 == 0))//第二个数据的输入判断
			{
				if(Data_2 <= 1000)//
				{
					Data_2 *= 10;
					Data_2 += K_Num;
					LCD_ShowNum(1,8,Data_2,4);
				}  
			}
			else if((K_Num == '=') && (CFlag_1 == 1) && (CFlag_2 == 0))//等号判断，按下等号即进行运算
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
				CFlag_2 = 1;  //按下等号后即锁死前面的入口，不允许改变Data_1 Data_2 Sym
				for(i=0;i<8;i++)
				{
					Num[i] = (Data_3/Pow(10,7-i))%10;
				}
				for(i=0;i<8;i++)
				{
					LCD_ShowNum(2,7+i,Num[i],1);
				}//显示 Data_3
			}
			else if(K_Num == 'C')  //按下相应键码C之后初始化
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