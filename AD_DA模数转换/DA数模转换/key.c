#include <REGX52.H>
#include "DELAY.H"
/**
   *	@brief	��ȡ������������
   *	@param	��
   *	@retval	�������룬��Χ��0-4���ް���ʱ����0��
   */	


unsigned char Key()
{
	unsigned char KeyNumber = 0;
	if(P3_1==0){Delayms(20);while(P3_1==0);Delayms(20);KeyNumber=1;}
	if(P3_0==0){Delayms(20);while(P3_0==0);Delayms(20);KeyNumber=2;}
	if(P3_2==0){Delayms(20);while(P3_2==0);Delayms(20);KeyNumber=3;}
	if(P3_3==0){Delayms(20);while(P3_3==0);Delayms(20);KeyNumber=4;}
	return KeyNumber;
}