#include <REGX52.H>

sbit OneWire_DQ = P3^7;

unsigned char OneWire_Init()		//�����߳�ʼ��
{
	unsigned char i;
	unsigned char AckBit;
	EA = 0;//�ر��ж�
	OneWire_DQ = 1;		 //��ʼ����ƽ
	OneWire_DQ = 0;		 //���͵�ƽ

	i = 247;while (--i); //��ʱ500us

	OneWire_DQ = 1;		 //���ߵ�ƽ

	i = 32;while (--i);  //��ʱ70us

	AckBit = OneWire_DQ;

	i = 247;while (--i); //��ʱ500us
	EA = 1;//���ж�
	return AckBit;
}
void OneWire_SendBit(unsigned char Bit)	   //����һλ
{
	unsigned char i;
	EA = 0;//�ر��ж�
	
	OneWire_DQ = 0;		 //���͵�ƽ

	i = 4;while (--i);	 //��ʱ10us
	OneWire_DQ = Bit;

	i = 24;while (--i);	 //��ʱ50us
	OneWire_DQ = 1;		 //�ͷŵ�ƽ
	EA = 1;//���ж�
}
unsigned char OneWire_ReceiveBit()		//����һλ
{
	unsigned char i;
	unsigned char Bit;
	EA = 0;//�ر��ж�
	OneWire_DQ = 0;		 //���͵�ƽ

	i = 2;while (--i);	 //��ʱ5us
	OneWire_DQ = 1;		 //�ͷŵ�ƽ���˺��ƽ�仯�ɴӻ�������

	i = 2;while (--i);	 //��ʱ5us�����в������������������Bit
	Bit = OneWire_DQ;

	i = 24;while (--i);	 //��ʱ50us
	EA = 1;//���ж�
	return Bit;

}

void OneWire_SendByte(unsigned char Byte)	  //����һ���ֽ�
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		OneWire_SendBit(Byte&(0x01<<i));//Byte&(0x01<<i)��Byte�ĵ�3λ���ͳ�ȥ����λ��ǰ�ȷ��ͣ�
	}
}
unsigned char OneWire_ReceiveByte()			 //����һ���ֽ�
{
	unsigned char i;
	unsigned char Byte = 0x00;

	for(i=0;i<8;i++)
	{
		if(OneWire_ReceiveBit()){Byte|=(0x01<<i);};
	}

	return Byte;
}












