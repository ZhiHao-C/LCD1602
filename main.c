#include <REGX52.H>
#include "LCD1602.h"
#include "delay.h"

void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;
	i = 4;
	j = 129;
	k = 119;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void main()
{
	LCD1602_Init();
//	LCD1602_showchar(2,11,'1');
	LCD_shownum(2,1,225,3);
	LCD_showsignednum(1,1,-25,2);
	LCD_showhexnum(1,7,175,2);
	LCD_showbinnum(2,5,0xaa,8);
	LCD1602_showstring(1,16,"welcome to china !");
	while(1)
	{
		LCD1602_writecommand(0x18);
		Delay500ms();
	}
}