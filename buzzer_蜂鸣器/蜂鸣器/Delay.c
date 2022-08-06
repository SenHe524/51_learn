#include <REGX52.H>

/**
   *	@brief	延时函数，@12.000MHz
   *	@param	无
   *	@retval	无
   */	  
void Delayms(unsigned int ms)		//@12.000MHz  延时函数
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