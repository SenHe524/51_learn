#include <REGX52.H>


/**
   *	@brief	�ⲿ�ж�0�ĳ�ʼ��
   *	@param	��
   *	@retval	��
   */
void Int0_Init()
{
	IT0 = 1; //�½��ش����ж�
	IE0 = 0; //�жϱ�־λ
	EX0 = 1; //�ⲿ0�ж�ʹ��
	EA  = 1; //�����ж�ʹ��
	PX0 = 1; //�����ȼ�

}
//
//void Int_0(void) interrupt 0
//{
//	
//}