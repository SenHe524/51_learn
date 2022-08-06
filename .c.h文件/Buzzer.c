#include <REGX52.H>
#include <INTRINS.H>

sbit Beep = P1^5;

/**
   *	@brief	��������ʱ������@12.000MHz
   *	@param	��
   *	@retval	��
   */	  
void Buzzer_Delay500us()		//@12.000MHz  ��ʱ����
{
	unsigned char i;

	_nop_();
	i = 247;
	while (--i);
}


/**
  * @brief      ��������������
  * @param  	ms������������ʱ��
  * @retval 	��
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