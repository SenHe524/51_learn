#include <REGX52.H>

typedef unsigned int uint;
typedef unsigned char uchar;
const char table[8]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,
0x7F};

void Scom_Init()	 //��ʼ������,�����ʣ�4800����Ƶ��
{
	TMOD = 0x20;//0010 0000
	TH1 = 0xF3;
	TL1 = 0xF3;
	PCON = 0x80;//1000 0000
	TR1= 1;
	SCON = 0x50;//0101 0000
	ES = 1;
	EA = 1;
}

void Usart() interrupt 4	  //�����ж�
{
    uchar receiveData;
	receiveData = SBUF;  //����һ������ �洢 ���ݻ�����SBUF�е����ݣ�
	RI = 0;	  //RI�����жϱ�־λ������ʱ�ɽ�������
	SBUF = receiveData;	   //�����ݴ�Ž����ݻ�����SBUF��
	while(!TI);  //����ʱ��TIΪ0��������ɺ�TIΪ1����ʱ!TIΪ0������while��
	TI = 0;	  //TI�����жϱ�־λ������ʱ�ɷ�������
}
	 

void main()
{
	Scom_Init();
	while(1);
}