#include <REGX52.H>

void Timer0_Init()
{
	//TMOD = 0x01;//0000 0001
	TMOD = TMOD & 0xF0; //TMOD & 上0xF0,TMOD高四位不变，低四位置零；
	TMOD = TMOD | 0x01; //TMOD | 上0x01,TMOD高四位不变，低四位置1；
	//上两行代码可以在保持TMOD前四位不变的情况下，对低四位进行赋值 
	TF0 = 0; //配置TCON中的TF0
	TR0 = 0; //定时器0不计时
	TL0 = 0;		//设置定时初始值
	TH0 = 0;		//设置定时初始值

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
