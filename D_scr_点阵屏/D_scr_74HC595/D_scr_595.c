#include <REGX52.H>
#include <Show_74HC595.H>
//点阵屏显示一个笑脸

void main()
{
	D_Scr_Init();
	while(1)
	{
		D_Scr_Show(0,0x3C);//0011 1100
		D_Scr_Show(1,0x42);//0100 0010
		D_Scr_Show(2,0xA9);//1010 1001
		D_Scr_Show(3,0x85);//1000 0101
		D_Scr_Show(4,0x85);//1000 0101
		D_Scr_Show(5,0xA9);//1010 1001
		D_Scr_Show(6,0x42);//0100 0010
		D_Scr_Show(7,0x3C);//0011 1100
	}
}