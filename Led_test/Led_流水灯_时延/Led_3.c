#include <REGX52.H>
#include <INTRINS.H>
const char table[8]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,
0x7F};
void Delayms(unsigned int ms)		//@12.000MHz  ÑÓÊ±º¯Êý
{
	unsigned char i, j;
	while(ms)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
		ms--;
	}
}

void main()
{
	int i;
	while(1)
	{
	    for(i=0;i<8;i++)
		{
			P2 = table[i];
			Delayms(500);
			P2 = 0xFF;
			Delayms(500);
		}
	}
}