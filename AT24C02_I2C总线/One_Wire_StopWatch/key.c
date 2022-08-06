#include <REGX52.H>
#include "DELAY.H"

unsigned char K_KeyNumber;

unsigned char Key()
{
	unsigned char Temp = 0;
	Temp = K_KeyNumber;
	K_KeyNumber = 0;
	return Temp;
}

unsigned char Key_GetState()
{
	unsigned char KeyNumber = 0;
	if(P3_1==0){KeyNumber=1;}
	if(P3_0==0){KeyNumber=2;}
	if(P3_2==0){KeyNumber=3;}
	if(P3_3==0){KeyNumber=4;}
	return KeyNumber;
}

void Key_Loop()
{
	static unsigned char N_State,L_State;
	unsigned int i;
	L_State	= N_State;
	N_State = Key_GetState();
	for(i=0;i<4;i++)
	{
		if(L_State==(i+1) && N_State==0)
		{
			K_KeyNumber = i+1;
			break;
		}	
	}
}