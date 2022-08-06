#include <REGX52.H>
#include "BUZZER.H"
#include "KEY.H"
#include "NIXIE.H"

unsigned char KeyNum;

void main()
{
	Nixie(1,0);
	while(1)
	{
		Nixie(8,0);
		KeyNum = Key();
		if(KeyNum)
		{
			Buzzer_Time(100);
			Nixie(1,KeyNum);
		}
	}
}