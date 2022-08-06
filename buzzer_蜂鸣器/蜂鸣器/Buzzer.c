#include <REGX52.H>
#include <INTRINS.H>

sbit Beep = P1^5;

/**
   *	@brief	蜂鸣器延时函数，@12.000MHz
   *	@param	无
   *	@retval	无
   */	  
void Buzzer_Delay500us()		//@12.000MHz  延时函数
{
	unsigned char i;

	_nop_();
	i = 247;
	while (--i);
}


/**
  * @brief      蜂鸣器启动函数
  * @param  	ms：蜂鸣器鸣叫时间
  * @retval 	无
  */
void Buzzer_Time(unsigned int ms)
{
	unsigned int i;
	for(i = 0; i < ms*2; i++)
	{
		Beep = !Beep;
		Buzzer_Delay500us();
	}
}