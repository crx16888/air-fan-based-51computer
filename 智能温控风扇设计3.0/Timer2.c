#include <REGX52.H>
void Timer2_Init(void)		//50毫秒@11.0592MHz
{
	T2MOD = 0;		//初始化模式寄存器
	T2CON = 0;		//初始化控制寄存器
	TL2 = 0x00;		//设置定时初始值
	TH2 = 0x00;		//设置定时初始值
	RCAP2L = 0x00;		//设置定时重载值
	RCAP2H = 0x00;		//设置定时重载值
	TR2 = 1;		//定时器2开始计时
}


