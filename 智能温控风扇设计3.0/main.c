#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "Nixie.h"
#include "Motor.h"
#include "IR.h"
#include "LCD1602.h"
#include "DS18B20.h"
#include "Timer2.h"
float T;
unsigned char Command,Speed;

void IR_Run()
{

	while(1)
	{
		if(IR_GetDataFlag())	//如果收到数据帧
		{
			Command=IR_GetCommand();		//获取遥控器命令码
				
			if(Command==IR_0){Speed=0;}		//根据遥控器命令码设置速度
			if(Command==IR_1){Speed=1;}
			if(Command==IR_2){Speed=2;}
			if(Command==IR_3){Speed=3;}
				
			if(Speed==0){Motor_SetSpeed(0);}	//速度输出
			if(Speed==1){Motor_SetSpeed(50);}
			if(Speed==2){Motor_SetSpeed(75);}
			if(Speed==3){Motor_SetSpeed(100);}
		}
		Nixie(1,Speed);						//数码管显示速度
	}
}
void Tem_Run()
{
	DS18B20_ConvertT();		//上电先转换一次温度，防止第一次读数据错误
	Delay(500);			//等待转换完成 
	Timer2_Init();	
	LCD_Init();
	LCD_ShowString(1,1,"Temperature:");
	while(1)
	{
		T=DS18B20_ReadT();
		DS18B20_ConvertT();		//上电先转换一次温度，防止第一次读数据错误
		Delay(1000);			//等待转换完成 
		T=DS18B20_ReadT();
		if(T<0)				//如果温度小于0
		{
			LCD_ShowChar(2,1,'-');	//显示负号
			T=-T;			//将温度变为正数
		}
		else				//如果温度大于等于0
		{
			LCD_ShowChar(2,1,'+');	//显示正号
		}
		LCD_ShowNum(2,2,T,3);		//显示温度整数部分
		LCD_ShowChar(2,5,'.');		//显示小数点
		LCD_ShowNum(2,6,(unsigned long)(T*10000)%10000,2);//显示温度小数部分
		if(T<26)
		{
			Motor_SetSpeed(30);
		}
		if(T>=26)
		{
			Motor_SetSpeed(80);
		}
	}
}
void main()
{
	Motor_Init();
	IR_Init();

	while(1)
	{
	if(IR_GetDataFlag())
	{	
		Command=IR_GetCommand();
		if(Command==IR_5){Tem_Run();}
		if(Command==IR_4){IR_Run();}
	}	
	}	
}

void Timer2_Routine() interrupt 5
{
	TF2=0;
	EXF2=0;
	P2=0;
	DS18B20_ConvertT();		//检测环境温度
	Delay(1000);			//等待转换完成	
}