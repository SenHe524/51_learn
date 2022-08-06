#include <REGX52.H>
#include "I2C.H"

#define AT24C02_Address_W 0xA0
#define AT24C02_Address_R 0xA1


/**
   *	@brief	AT24C02д���ֽ�
   *	@param	WordAddress��д���ַ  Data��д�������
   *	@retval	��
   */
void AT24C02_WriteByte(unsigned char WordAddress,Data)
{
	I2C_Start();
	I2C_SendByte(AT24C02_Address_W);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_SendByte(Data);
	I2C_ReceiveAck();
	I2C_Stop();

}


/**
   *	@brief	AT24C02��ȡһ���ֽ�
   *	@param	WordAddress����ȡ���ݵĵ�ַ
   *	@retval	Data����ȡ��������
   */
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data;
	I2C_Start();
	I2C_SendByte(AT24C02_Address_W);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_Start();
	I2C_SendByte(AT24C02_Address_R);
	I2C_ReceiveAck();
    Data = I2C_ReceiveByte();
	I2C_SendAck(1);
	I2C_Stop();

	return Data;
}
