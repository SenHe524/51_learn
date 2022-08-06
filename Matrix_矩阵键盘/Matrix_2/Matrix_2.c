#include <REGX52.H>
#include "DELAY.H"
#include "LCD1602.H"
#include "NIXIE.H"
#include "MATRIX_NUM.H"

unsigned char K_Num;
unsigned int PassWord = 1568;
unsigned int PassWord_Temp = 0;
unsigned int Count = 0;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"Password:");
	LCD_ShowNum(2,1,PassWord_Temp,4);	 //������ʾ
	while(1)
	{
		K_Num = Matrix_Num();
		if(K_Num)
		{
			if(K_Num<=10) //�������룺ֻ�а���1��10�����ã�1-9��Ӧ1-9��10��Ӧ0��
			{
				if(Count<4)		 //������λ����
				{
					PassWord_Temp *= 10;
					PassWord_Temp += K_Num%10;
					Count++;
				}
				LCD_ShowNum(2,1,PassWord_Temp,4);	 //������ʾ
			}
			if(K_Num==11)
			{
				if(PassWord_Temp==PassWord)
				{
					LCD_ShowString(1,14,"OK!");
				}
				else
				{
					LCD_ShowString(1,14,"ERR");			
				}
				PassWord_Temp = 0;
				Count = 0;
				LCD_ShowNum(2,1,PassWord_Temp,4);	 //������ʾ
			}
			if(K_Num==12)
			{
				PassWord_Temp = 0;
				Count = 0;
				LCD_ShowNum(2,1,PassWord_Temp,4);	 //������ʾ
			}			
		}

	}
}