#include <REGX52.H>

/**
   *	@brief	��ʱ������@12.000MHz
   *	@param	��
   *	@retval	��
   */	  
void Delayms(unsigned int ms)		//@12.000MHz  ��ʱ����
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