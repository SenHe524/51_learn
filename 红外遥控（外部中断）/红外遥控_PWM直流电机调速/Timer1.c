#include <REGX52.H>
/**
   *	@brief	��ʱ��1�ĳ�ʼ����1����@12MHZ
   *	@param	��
   *	@retval	��
   */	
   
void Timer1_Init()
{
	//TMOD = 0x01;//0000 0001
	TMOD = TMOD & 0x0F; //TMOD & ��0xF0,TMOD����λ���䣬����λ���㣻
	TMOD = TMOD | 0x10; //TMOD | ��0x01,TMOD����λ���䣬����λ��1��
	//�����д�������ڱ���TMODǰ��λ���������£��Ե���λ���и�ֵ 
	TF1 = 0; //����TCON�е�TF0
	TR1 = 1;
	TL1 = 0x18;		//���ö�ʱ��ʼֵ
	TH1 = 0xFC;		//���ö�ʱ��ʼֵ
	ET1 = 1;
	EA = 1;
	PT1 = 0;
}

/* ��ʱ���ж�ģ��
void Timer1_Routine() interrupt 3
{
	static unsigned int T1count;
	TL1 = 0x18;		//���ö�ʱ��ʼֵ
	TH1 = 0xFC;		//���ö�ʱ��ʼֵ
	if(T0count>=1000)
	{
		T0count = 0;
	}
	T1count++;

}
*/