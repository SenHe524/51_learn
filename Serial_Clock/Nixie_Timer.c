#include <REGX52.H>
unsigned char Nixie_Num[]={0x3F,0x06,0X5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,
							    0x77,0x7C,0x39,0x5E,0x79,0x71,0x00,0x40};

unsigned char Nixie_Buf[9] = {0,1,1,1,1,1,1,1,1};
void Nixie(unsigned char Location,Number)
{
	P0 = Nixie_Num[16];
    switch(Location)
	{
		case 1:P2_4 = 1;P2_3 = 1;P2_2 = 1;;break;
		case 2:P2_4 = 1;P2_3 = 1;P2_2 = 0;;break;
		case 3:P2_4 = 1;P2_3 = 0;P2_2 = 1;;break;
		case 4:P2_4 = 1;P2_3 = 0;P2_2 = 0;;break;
		case 5:P2_4 = 0;P2_3 = 1;P2_2 = 1;;break;
		case 6:P2_4 = 0;P2_3 = 1;P2_2 = 0;;break;
		case 7:P2_4 = 0;P2_3 = 0;P2_2 = 1;;break;
		case 8:P2_4 = 0;P2_3 = 0;P2_2 = 0;;break;
	}
	P0 = Nixie_Num[Number];
}
void Nixie_Loop()
{
	static unsigned char i = 1;
	Nixie(i,Nixie_Buf[i]);
	i++;
	i = i%9+1;
}
void Nixie_Scan(unsigned char Location,Number)
{
	Nixie_Buf[Location] = Number;
}