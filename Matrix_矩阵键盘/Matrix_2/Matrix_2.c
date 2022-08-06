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
	LCD_ShowNum(2,1,PassWord_Temp,4);	 //更新显示
	while(1)
	{
		K_Num = Matrix_Num();
		if(K_Num)
		{
			if(K_Num<=10) //输入密码：只有按下1—10才有用：1-9对应1-9，10对应0；
			{
				if(Count<4)		 //输入四位密码
				{
					PassWord_Temp *= 10;
					PassWord_Temp += K_Num%10;
					Count++;
				}
				LCD_ShowNum(2,1,PassWord_Temp,4);	 //更新显示
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
				LCD_ShowNum(2,1,PassWord_Temp,4);	 //更新显示
			}
			if(K_Num==12)
			{
				PassWord_Temp = 0;
				Count = 0;
				LCD_ShowNum(2,1,PassWord_Temp,4);	 //更新显示
			}			
		}

	}
}