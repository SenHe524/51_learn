#include <REGX52.H>
/**
   *	@brief	��ʱ��0�ĳ�ʼ����1����@12MHZ
   *	@param	��
   *	@retval	��
   */	
   
void Timer0_Init()
{
	//TMOD = 0x01;//0000 0001
	TMOD = TMOD & 0xF0; //TMOD & ��0xF0,TMOD����λ���䣬����λ���㣻
	TMOD = TMOD | 0x01; //TMOD | ��0x01,TMOD����λ���䣬����λ��1��
	//�����д�������ڱ���TMODǰ��λ���������£��Ե���λ���и�ֵ 
	TF0 = 0; //����TCON�е�TF0
	TR0 = 1;
	TL0 = 0x18;		//���ö�ʱ��ʼֵ
	TH0 = 0xFC;		//���ö�ʱ��ʼֵ
	ET0 = 1;
	EA = 1;
	PT0 = 0;
}

/* ��ʱ���ж�ģ��
void Timer0_Routine() interrupt 1
{
	static unsigned int T0count;
	TL0 = 0x18;		//���ö�ʱ��ʼֵ
	TH0 = 0xFC;		//���ö�ʱ��ʼֵ
	if(T0count>=1000)
	{
		T0count = 0;
	}
	T0count++;

}
*/