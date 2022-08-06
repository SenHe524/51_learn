#include <REGX52.H>
#include "LCD1602.H"
#include "MATRIX_NUM.H"

unsigned char K_Num;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"MatrixKey");
	
	while(1)
	{
		K_Num = Matrix_Num();
		if(K_Num)
		{
			LCD_ShowNum(2,1,K_Num,2);
		}
	}
}