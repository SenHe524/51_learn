#include <REGX52.H>
#include "DELAY.H"

unsigned char K_KeyNumber;


/**
   *	@brief	��ȡ��������
   *	@param	��
   *	@retval	���µİ������룬��Χ;0-4,0��ʾ�ް�������
   */
unsigned char Key()
{
	unsigned char Temp = 0;
	Temp = K_KeyNumber;
	K_KeyNumber = 0;
	return Temp;
}
/**
   *	@brief	��ȡ��ǰ������״̬�������������ּ��
   *	@param	��
   *	@retval	���µİ����ļ��룬��Χ;0-4,0��ʾ�ް�������
   */
unsigned char Key_GetState()
{
	unsigned char KeyNumber = 0;
	if(P3_1==0){KeyNumber=1;}
	if(P3_0==0){KeyNumber=2;}
	if(P3_2==0){KeyNumber=3;}
	if(P3_3==0){KeyNumber=4;}
	return KeyNumber;
}


/**
   *	@brief	�����������������ж��е���
   *	@param	��
   *	@retval	��
   */
void Key_Loop()
{
	static unsigned char N_State,L_State;
	unsigned int i;
	L_State	= N_State;	  //����״̬����
	N_State = Key_GetState();		 //��ȡ��ǰ����״̬
	//����һ���жϰ������£���������ж�δ���£����ж�Ϊ�������Դ���Ϊ���ּ��	
	for(i=0;i<4;i++)
	{
		if(L_State==(i+1) && N_State==0)
		{
			K_KeyNumber = i+1;
			break;
		}	
	}
}