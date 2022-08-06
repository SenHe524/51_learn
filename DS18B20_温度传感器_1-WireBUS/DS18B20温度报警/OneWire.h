#ifndef _ONEWIRE_H_
#define _ONEWIRE_H_

unsigned char OneWire_Init();		           //单总线初始化
void OneWire_SendBit(unsigned char Bit);	   //发送一位
unsigned char OneWire_ReceiveBit();		       //接收一位
void OneWire_SendByte(unsigned char Byte);	   //发送一个字节
unsigned char OneWire_ReceiveByte();		   //接收一个字节

#endif