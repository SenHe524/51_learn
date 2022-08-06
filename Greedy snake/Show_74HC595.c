#include <REGX52.H>
#include "DELAY.H"

sbit SER = P3^4;  //SER
sbit SCK = P3^6;  //SRCLK
sbit RCK = P3^5;  //RCLK

#define D_Scr_Port P0		//��P0��������λD_Scr_Port

/**
   *	@brief	��������ʼ��
   *	@param	��
   *	@retval	��
   */	
void D_Scr_Init()
{
	SCK = 0;
    RCK = 0;
}

/**
   *	@brief	74HC595д��һ���ֽ�
   *	@param	Byte:Ҫд����ֽ�
   *	@retval	��
   */	
void WriteByte_74595(unsigned char Byte)
{
	unsigned int i;
	//16����Byte��ֵ��λSER��Byte��0��SER��1
	//Byte&1000 0000,Byte���λΪ1,SERΪ1(1000 0000Ϊ����)
	//Byte���λΪ0,SERΪ0(0000 0000Ϊ0)
	for(i=0;i<8;i++)
	{
		SER = Byte&(0x80>>i);//0x80>>i   0x80λ����iλ  
	    SCK = 1;//�ߵ�ƽ��λ
	    SCK = 0;//�͵�ƽ,Ϊ��һ�θߵ�ƽ��׼��
	}
	RCK = 1;
	RCK = 0;				 
}

/**
   *	@brief	 LED��������ʾһ������
   *	@param	 line:��ʾ���ݵ��У���Χ��0~7��0Ϊ�����������У�7Ϊ������
   *	@param	 Data:��Ҫ��ʾ�����ݣ���λ���ϣ�1����0��
   *	@retval	 ��
   */	
void D_Scr_Show(unsigned char line,unsigned char Data)
{
	WriteByte_74595(Data);
	D_Scr_Port = ~(0x80>>line); //����line�е�P0��Ϊ�͵�ƽ��ʹ�䵼ͨ����ʹLED�ܵ���
	Delayms(1);	//��ʱ
	D_Scr_Port = 0xFF;	//λ����
}
