#include <REG52.H>
#include "OneWire.h"

//DS18B20指令
#define DS18B20_SKIP_ROM			0xCC
#define DS18B20_CONVERT_T			0x44
#define DS18B20_READ_SCRATCHPAD 	0xBE

/**
  * @brief  DS18B20开始温度变换
  * @param  无
  * @retval 无
  */
void DS18B20_ConvertT(void)
{
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_CONVERT_T);//开始从环境中采集温度
}

float DS18B20_ReadT(void)
{
	unsigned char TLSB,TMSB;
	int Temp;
	float T;
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_READ_SCRATCHPAD);//从SCRATCHPAD寄存器的两个存储区域内读取环境中测得的温度
	TLSB=OneWire_ReceiveByte();//接收低八位字节温度
	TMSB=OneWire_ReceiveByte();//接收高八位字节温度（前五位为正负号）
	Temp=(TMSB<<8)|TLSB;
	T=Temp/16.0;//乘上0.625表示真实的温度，DS18B20里的分度值是0.625
	return T;
}