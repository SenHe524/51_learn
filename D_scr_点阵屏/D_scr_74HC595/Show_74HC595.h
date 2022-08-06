#ifndef _Show_74HC595_H_
#define _Show_74HC595_H_

void D_Scr_Init();
void WriteByte_74595(unsigned char Byte);
void D_Scr_Show(unsigned char line,unsigned char Data);


#endif