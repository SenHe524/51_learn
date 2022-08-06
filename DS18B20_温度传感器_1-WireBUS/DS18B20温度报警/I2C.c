#include <REGX52.H>

sbit I2C_SCL  = P2^1;
sbit I2C_SDA  = P2^0;


/**
   *	@brief	I2C��ʼ
   *	@param	��
   *	@retval	��
   */	
void I2C_Start()
{
	//�ȼ��SCL��SDA�ĵ�ƽ
	I2C_SCL = 1;
	I2C_SDA = 1;
	//������SDA��SCL
	I2C_SDA = 0;
	I2C_SCL = 0;
}

/**
   *	@brief	I2Cֹͣ
   *	@param	��
   *	@retval	��
   */	
void I2C_Stop()
{
	I2C_SDA = 0;	 
	I2C_SCL = 1;
	I2C_SDA = 1;
}

/**
   *	@brief	I2C����һ���ֽ�
   *	@param	Byte��Ҫ���͵��ֽ�
   *	@retval	��
   */	
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		I2C_SDA = Byte&(0x80>>i);//��Byte��8-iλȡ������ֵ��SDA	 
		I2C_SCL = 1;  //��ʱ��ƽ��תʱ���㹻��Ƭ����Ӧ������󲻱�Delayһ��ʱ�䣬������SCL
		I2C_SCL = 0;
	
	}
}

/**
   *	@brief	I2C����һ���ֽ�
   *	@param	��
   *	@retval	Byte:���յ����ֽ�
   */
unsigned char I2C_ReceiveByte()
{
	unsigned char i,Byte = 0x00;
	I2C_SDA = 1;  //��1�ͷ�����
	for(i=0;i<8;i++)
	{
		I2C_SCL = 1;  //��1���ߵ�ƽ��ȡSDA
		if(I2C_SDA){Byte|=(0x80>>i);}
		I2C_SCL = 0; 	
	}
	return Byte;
}

/**
   *	@brief	I2C����Ӧ��
   *	@param	AckBit��Ӧ��λ	 0ΪӦ��1Ϊ��Ӧ��
   *	@retval	��
   */
void I2C_SendAck(unsigned char AckBit)	
{
	I2C_SDA = AckBit;	 
	I2C_SCL = 1; 
	I2C_SCL = 0;
}

/**
   *	@brief	I2C����Ӧ��
   *	@param	��
   *	@retval	AckBit�����յ���Ӧ��λ  0ΪӦ��1ΪδӦ��
   */
unsigned char I2C_ReceiveAck()		
{
	unsigned char AckBit = 0;
	I2C_SDA = 1;  //�ͷ�SDA��SDA�ڵ͵�ƽ�ڼ��޷���ȡ���ߵ�ƽ�ڼ���Զ�ȡ	 
	I2C_SCL = 1;  //SCL�ڵ͵�ƽ�ڼ��޷���ȡ���ߵ�ƽ�ڼ���Զ�ȡ
	if(I2C_SDA){AckBit = 1;}
	I2C_SCL=0;
	return AckBit;
}

