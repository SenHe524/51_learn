#ifndef _DS1302_Fuction_H_
#define _DS1302_Fuction_H_

extern unsigned char DS1302_TIME[];

void DS1302_Init();
void DS1302_WriteByte(unsigned char Command,unsigned char Data);
char DS1302_ReadByte(unsigned char Command);
void DS1302_SetTime();
void DS1302_ReadTime();

#endif