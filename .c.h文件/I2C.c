#include <REGX52.H>

sbit I2C_SCL  = P2^1;
sbit I2C_SDA  = P2^0;


/**
   *	@brief	I2C开始
   *	@param	无
   *	@retval	无
   */	
void I2C_Start()
{
	//先检查SCL和SDA的电平
	I2C_SCL = 1;
	I2C_SDA = 1;
	//再拉低SDA和SCL
	I2C_SDA = 0;
	I2C_SCL = 0;
}

/**
   *	@brief	I2C停止
   *	@param	无
   *	@retval	无
   */	
void I2C_Stop()
{
	I2C_SDA = 0;	 
	I2C_SCL = 1;
	I2C_SDA = 1;
}

/**
   *	@brief	I2C发送一个字节
   *	@param	Byte：要发送的字节
   *	@retval	无
   */	
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		I2C_SDA = Byte&(0x80>>i);//将Byte的8-i位取出并赋值给SDA	 
		I2C_SCL = 1;  //此时电平翻转时间足够单片机反应，故其后不必Delay一段时间，再拉低SCL
		I2C_SCL = 0;
	
	}
}

/**
   *	@brief	I2C接收一个字节
   *	@param	无
   *	@retval	Byte:接收到的字节
   */
unsigned char I2C_ReceiveByte()
{
	unsigned char i,Byte = 0x00;
	I2C_SDA = 1;  //置1释放总线
	for(i=0;i<8;i++)
	{
		I2C_SCL = 1;  //置1，高电平读取SDA
		if(I2C_SDA){Byte|=(0x80>>i);}
		I2C_SCL = 0; 	
	}
	return Byte;
}

/**
   *	@brief	I2C发送应答
   *	@param	AckBit：应答位	 0为应答，1为非应答
   *	@retval	无
   */
void I2C_SendAck(unsigned char AckBit)	
{
	I2C_SDA = AckBit;	 
	I2C_SCL = 1; 
	I2C_SCL = 0;
}

/**
   *	@brief	I2C接收应答
   *	@param	无
   *	@retval	AckBit：接收到的应答位  0为应答，1为未应答
   */
unsigned char I2C_ReceiveAck()		
{
	unsigned char AckBit = 0;
	I2C_SDA = 1;  //释放SDA：SDA在低电平期间无法读取，高电平期间可以读取	 
	I2C_SCL = 1;  //SCL在低电平期间无法读取，高电平期间可以读取
	if(I2C_SDA){AckBit = 1;}
	I2C_SCL=0;
	return AckBit;
}

