#include <REGX52.H>
const char table[8]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,
0x7F};

void Delayms(unsigned int ms)		//@12.000MHz
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
	while(1)
	{
////      ���°��������̸ı�LED״̬		
//		if(P3_1==0)
//		{
//			P2_0=~P2_0;
//			Delayms(20);
//			while(P3_1==0);
//			Delayms(20);	
//		}

//		���°��������ɿ�֮���ٸı�LED״̬
		if(P3_1==0)
		{
			Delayms(20);
			while(P3_1==0);
			Delayms(20);
            P2_0=~P2_0;	
		}
	}
}