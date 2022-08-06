#include <REGX52.H>
#include "I2C.H"

#define AT24C02_Address_W 0xA0
#define AT24C02_Address_R 0xA1


/**
   *	@brief	AT24C02���ֽ�д������֡����WordAddress��д��Data
   *	@param	WordAddress��д���ַ  Data��д�������
   *	@retval	��
   */
void AT24C02_WriteByte(unsigned char WordAddress,Data)
{
	I2C_Start();	                       //��ʼ�ź�
	I2C_SendByte(AT24C02_Address_W);	   //�ӻ���ַ��д�ź�
	I2C_ReceiveAck();					   //�ӻ�����Ӧ��
	I2C_SendByte(WordAddress);			   //����д��ĵ�ַ
	I2C_ReceiveAck();					   //�ӻ�����Ӧ��
	I2C_SendByte(Data);					   //д������
	I2C_ReceiveAck();					   //�ӻ�����Ӧ��
	I2C_Stop();							   //�����ź�

}


/**
   *	@brief	AT24C02���ֽڶ�ȡ����֡����WordAddress����ȡ����
   *	@param	WordAddress����ȡ���ݵĵ�ַ
   *	@retval	Data����ȡ��������
   */
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data;
	I2C_Start();					   //��ʼ�ź�
	I2C_SendByte(AT24C02_Address_W);   //�ӻ���ַ��д�ź�
	I2C_ReceiveAck();				   //�ӻ�����Ӧ��
	I2C_SendByte(WordAddress);		   //���ݶ�ȡ�ĵ�ַ
	I2C_ReceiveAck();				   //����Ӧ��
	/*
		ע���˴�ʡ����һ��I2C_Stop������AT24C02�����ݶ�ȡʵ����
	        ��I2Cͨ�ŵ�д��Ͷ�ȡ�ĸ��Ͻṹ��д�룺ȷ���ӻ���ַ�����ݴ洢��ַ
			��ȡ���Ӵ洢��ַ����ȡ����Data
	*/
	I2C_Start();					   //��ʼ�ź�
	I2C_SendByte(AT24C02_Address_R);   //�ӻ���ַ�����ź�
	I2C_ReceiveAck();				   //�ӻ�Ӧ��
    Data = I2C_ReceiveByte();		   //������������
	I2C_SendAck(1);					   //������ɣ��������ͷ�Ӧ��1��
	I2C_Stop();						   //�����ź�

	return Data;
}
