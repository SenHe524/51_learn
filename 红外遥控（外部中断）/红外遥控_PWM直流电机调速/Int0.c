#include <REGX52.H>


/**
   *	@brief	外部中断0的初始化
   *	@param	无
   *	@retval	无
   */
void Int0_Init()
{
	IT0 = 1; //下降沿触发中断
	IE0 = 0; //中断标志位
	EX0 = 1; //外部0中断使能
	EA  = 1; //所有中断使能
	PX0 = 1; //高优先级

}
//
//void Int_0(void) interrupt 0
//{
//	
//}