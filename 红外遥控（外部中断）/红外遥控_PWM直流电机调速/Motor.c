#include <REGX52.H>
#include "TIMER1.H"

sbit Motor = P1^0;

unsigned char Counter,Compare;	  //�������Ϊ����

/**
  * @brief      �����ʼ��
  * @param  	��
  * @retval 	��
  */
void Motor_Init()
{
	Timer1_Init();
}
/**
  * @brief      ����ٶ�����
  * @param  	 Speed��0-100��
  * @retval 	 ��
  */
void Motor_SetSpeed(unsigned char Speed)
{
	Compare = Speed;
}
/**
  * @brief      ��ʱ��1�жϣ�ʵ��PWM
  * @param  
  * @retval 
  */
void Timer1_Routine() interrupt 3
{
	TL1 = 0x9C;		//���ö�ʱ��ʼֵ
	TH1 = 0xFF;		//���ö�ʱ��ʼֵ
	Counter++;
	if(Counter>=100)
	{
		Counter = 0;
	}
	// Counter %= 100;  ����ʵ��if���Ĺ���
	if(Compare > Counter)
	{
		Motor = 1;
	}
	else
	{
		Motor = 0;
	}
}