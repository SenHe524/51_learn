#include <REGX52.H>

sbit XPT2046_DIN = P3^4;
sbit XPT2046_CS = P3^5;
sbit XPT2046_DCLK = P3^6;
sbit XPT2046_DOUT = P3^7;

unsigned int XPT2046_ReadAD(unsigned char Command)
{
	unsigned int AD_Value=0;
	unsigned char i;
	XPT2046_CS = 0;				   //CS����ʱ��ʼ
	
	for(i=0;i<8;i++)
	{
		XPT2046_DCLK = 0;			   //DCLK����
		XPT2046_DIN = Command&(0x80>>i);	   //�����ط���
		XPT2046_DCLK = 1;			   //DCLK��һ����������	
	}
	 
	XPT2046_DCLK = 0;			   //���ͽ���������DCLK

	for(i=0;i<16;i++)
	{
		XPT2046_DCLK = 1;			   
		XPT2046_DCLK = 0;			   //DCLK��һ����������½���
		if(XPT2046_DOUT){AD_Value|=(0x8000>>i);}
	}
	XPT2046_DCLK = 0;			   //DCLK����
	XPT2046_CS = 1;				   //CS��һʱ�����

	if(Command&0x08)
	{
	   return AD_Value>>8;
	}
	else
	{
		return AD_Value>>4;
	}
}
