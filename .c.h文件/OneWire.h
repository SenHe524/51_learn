#ifndef _ONEWIRE_H_
#define _ONEWIRE_H_

unsigned char OneWire_Init();		           //�����߳�ʼ��
void OneWire_SendBit(unsigned char Bit);	   //����һλ
unsigned char OneWire_ReceiveBit();		       //����һλ
void OneWire_SendByte(unsigned char Byte);	   //����һ���ֽ�
unsigned char OneWire_ReceiveByte();		   //����һ���ֽ�

#endif