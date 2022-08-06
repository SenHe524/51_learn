#include <REGX52.H>

void Timer0_Init()
{
	//TMOD = 0x01;//0000 0001
	TMOD = TMOD & 0xF0; //TMOD & ��0xF0,TMOD����λ���䣬����λ���㣻
	TMOD = TMOD | 0x01; //TMOD | ��0x01,TMOD����λ���䣬����λ��1��
	//�����д�������ڱ���TMODǰ��λ���������£��Ե���λ���и�ֵ 
	TF0 = 0; //����TCON�е�TF0
	TR0 = 0; //��ʱ��0����ʱ
	TL0 = 0;		//���ö�ʱ��ʼֵ
	TH0 = 0;		//���ö�ʱ��ʼֵ

}
void Timer0_SetCounter(unsigned int Value)
{
	TH0 = Value/256;
	TL0 = Value%256;
}

unsigned int Timer0_GetCounter()
{
	return (TH0<<8)|TL0;
}

void Timer0_Run(unsigned char flag)
{
	TR0 = flag;	
}
