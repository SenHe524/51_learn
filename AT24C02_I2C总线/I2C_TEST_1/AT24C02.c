#include <REGX52.H>
#include "I2C.H"

#define AT24C02_Address_W 0xA0
#define AT24C02_Address_R 0xA1


/**
   *	@brief	AT24C02的字节写入数据帧：在WordAddress处写入Data
   *	@param	WordAddress：写入地址  Data：写入的数据
   *	@retval	无
   */
void AT24C02_WriteByte(unsigned char WordAddress,Data)
{
	I2C_Start();	                       //起始信号
	I2C_SendByte(AT24C02_Address_W);	   //从机地址及写信号
	I2C_ReceiveAck();					   //从机接收应答
	I2C_SendByte(WordAddress);			   //数据写入的地址
	I2C_ReceiveAck();					   //从机接收应答
	I2C_SendByte(Data);					   //写入数据
	I2C_ReceiveAck();					   //从机接收应答
	I2C_Stop();							   //结束信号

}


/**
   *	@brief	AT24C02的字节读取数据帧：从WordAddress处读取数据
   *	@param	WordAddress：读取数据的地址
   *	@retval	Data：读取到的数据
   */
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data;
	I2C_Start();					   //起始信号
	I2C_SendByte(AT24C02_Address_W);   //从机地址及写信号
	I2C_ReceiveAck();				   //从机接收应答
	I2C_SendByte(WordAddress);		   //数据读取的地址
	I2C_ReceiveAck();				   //接收应答
	/*
		注：此处省略了一个I2C_Stop，所以AT24C02的数据读取实际上
	        是I2C通信的写入和读取的复合结构，写入：确定从机地址和数据存储地址
			读取：从存储地址处读取数据Data
	*/
	I2C_Start();					   //起始信号
	I2C_SendByte(AT24C02_Address_R);   //从机地址及读信号
	I2C_ReceiveAck();				   //从机应答
    Data = I2C_ReceiveByte();		   //主机接收数据
	I2C_SendAck(1);					   //接收完成，主机发送非应答（1）
	I2C_Stop();						   //结束信号

	return Data;
}
