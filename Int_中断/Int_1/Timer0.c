#include <REGX52.H>
/**
   *	@brief	定时器0的初始化，1毫秒@12MHZ
   *	@param	无
   *	@retval	无
   */	
   
void Timer0_Init()
{
	//TMOD = 0x01;//0000 0001
	TMOD = TMOD & 0xF0; //TMOD & 上0xF0,TMOD高四位不变，低四位置零；
	TMOD = TMOD | 0x01; //TMOD | 上0x01,TMOD高四位不变，低四位置1；
	//上两行代码可以在保持TMOD前四位不变的情况下，对低四位进行赋值 
	TF0 = 0; //配置TCON中的TF0
	TR0 = 1;
	TL0 = 0x18;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	ET0 = 1;
	EA = 1;
	PT0 = 0;
}

/* 定时器中断模板
void Timer0_Routine() interrupt 1
{
	static unsigned int T0count;
	TL0 = 0x18;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	if(T0count>=1000)
	{
		T0count = 0;
	}
	T0count++;

}
*/