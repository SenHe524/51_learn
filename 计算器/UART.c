#include <REGX52.H>

/*		B7   B6   B5   B4   B3   B2   B1   B0
scon :  SM0	 SM1  SM2  REN  TB8  TB9  TI   RI
		SM0��SM1���ƴ��ڹ�����ʽ��REN����ʹ�ܣ���1ʱ������գ�����ʱ��ֹ���գ���
		TI��RI�ֱ�Ϊ�����жϺͽ����жϣ���1ʱ���ͻ��߽����ж����
		��������и�λ���㣬��ʱ�ɷ��ͻ�������ݣ�
*/

/**
   *	@brief	���ڳ�ʼ��	 //4800bps @12MHZ
   *	@param	��
   *	@retval	��
   */	
void UART_Init()			 
{
	SCON = 0x50;
	PCON = 0x80;
	TMOD &= 0x0F;	//�����ʱ��1ģʽλ
	TMOD |= 0x20; 	//���ö�ʱ��1Ϊ8λ�Զ���װģʽ
	TH1 = 0xF3;	   //���ö�ʱ��ֵ  F3=243;256-243=13us;1/13us=0.0769230769230769MHZ
	TL1 = 0xF3;	   //���ö�ʱ��װֵ	   0.076923/16=0.004807MHZ  ��4807bps
	TR1 = 1; 	   //������ʱ��1
	EA = 1;
	ES = 1;
	
}

/**
   *	@brief	���ڷ���һ���ֽ�����
   *	@param	Data:Ҫ����������
   *	@retval	��
   */	
void UART_SendByte(unsigned char Data)
{
	SBUF = Data;
	while(!TI);
	TI = 0;
}