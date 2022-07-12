#include <REGX52.H>
#include <delay.h>
sbit EN=P2^7;
sbit RS=P2^6;
sbit RW=P2^5;

unsigned int get10_power(unsigned char n)
{
	unsigned char i;
	unsigned char result=1;
	for(i=n;i>0;i--)
	{
		result=10*result;
	}
	return result;
}

unsigned int get16_power(unsigned char n)
{
	unsigned char i;
	unsigned char result=1;
	for(i=n;i>0;i--)
	{
		result=16*result;
	}
	return result;
}

unsigned int get2_power(unsigned char n)
{
	unsigned char i;
	unsigned char result=1;
	for(i=n;i>0;i--)
	{
		result=2*result;
	}
	return result;
}

void LCD1602_writecommand(unsigned char command)
{
	EN=0;
	RS=0;
	RW=0;
	P0=command;
	EN=1;
	delay_ms(1);
	EN=0;
	delay_ms(1);
}

void LCD1602_writedata(unsigned char Data)
{
	EN=0;
	RS=1;
	RW=0;
	P0=Data;
	EN=1;
	delay_ms(1);
	EN=0;
	delay_ms(1);
}

void LCD1602_Init()
{
	LCD1602_writecommand(0x38);        // 16*2显示，5*7点阵，8位数据口
	LCD1602_writecommand(0x0C);        // 开显示，不显示光标
	LCD1602_writecommand(0x06);        // 地址加1，当写入数据后光标右移
	LCD1602_writecommand(0x01);        // 清屏
}


void LCD1602_showchar(char r,char c,char Char)
{
	if(r<=2&&c<=16)
	{
		switch(r)
		{
			case 1:
				LCD1602_writecommand(0x80+c-1);
				LCD1602_writedata(Char);break;
			case 2:
				LCD1602_writecommand(0x80+0x40+c-1);
				LCD1602_writedata(Char);break;
		}
	}
}


void LCD1602_showstring(char r,char c,char string[])
{
	if(r<=2&&c<=16)
	{
		switch (r)
		{
			case 1:
				LCD1602_writecommand(0x80+c-1);
				while(*string!=0)
				{
					LCD1602_writedata(*string);
					string++;
				}
				break;
			case 2:
				LCD1602_writecommand(0x80+0x40+c-1);
				while(*string!=0)
				{
					LCD1602_writedata(*string);
					string++;
				}
				break;
		}
	}
}

void LCD_shownum(unsigned char r,unsigned char c,unsigned int num,unsigned char length)
{
//	unsigned int a;
	unsigned char i;
//	unsigned int T;
	if(r<=2&&c<=16)
	{
		switch (r)
		{
			case 1:
				LCD1602_writecommand(0x80+c-1);
				for(i=length;i>0;i--)
				{
//					a=get10_power(i-1);
//					T=(num/get10_power(i-1))%10+0x30;
					LCD1602_writedata((num/get10_power(i-1))%10+0x30);
				}
				break;
			case 2:
				LCD1602_writecommand(0x80+0x40+c-1);
				for(i=length;i>0;i--)
				{
					LCD1602_writedata((num/get10_power(i-1))%10+0x30);
				}
				break;
		}
	}
}



void LCD_showsignednum(unsigned char r,unsigned char c, int num,unsigned char length)
{
	unsigned int number;
	unsigned char i;
	if(r<=2&&c<=16)
	{
		switch (r)
		{
			case 1:
				LCD1602_writecommand(0x80+c-1);
				if(num>=0)
				{
					number=num;
					LCD1602_writedata('+');
				}
				if(num<0)
				{
					number=-num;
					LCD1602_writedata('-');
				}
				for(i=length;i>0;i--)
				{
					LCD1602_writedata((number/get10_power(i-1))%10+0x30);
				}
				break;
			case 2:
				LCD1602_writecommand(0x80+0x40+c-1);
				if(num>=0)
				{
					number=num;
					LCD1602_writedata('+');
				}
				if(num<0)
				{
					number=-num;
					LCD1602_writedata('-');
				}
				for(i=length;i>0;i--)
				{
					LCD1602_writedata((number/get10_power(i-1))%10+0x30);
				}
				break;
		}
	}
}


void LCD_showhexnum(unsigned char r,unsigned char c,unsigned int num,unsigned char length)
{
	unsigned char i;
	unsigned int T;
	
	if(r<=2&&c<=16)
	{
		switch (r)
		{
			case 1:
				LCD1602_writecommand(0x80+c-1);
				LCD1602_writedata('0');
				LCD1602_writedata('x');
				for(i=length;i>0;i--)
				{
					
					T=(num/get16_power(i-1))%16;
					if(T>=10)
					{
						T=T+0x07;
						LCD1602_writedata(T+0x30);
					}
					if(T<10)
					{
						LCD1602_writedata((num/get16_power(i-1))%16+0x30);
					}
					
				}
				break;
			case 2:
				LCD1602_writecommand(0x80+0x40+c-1);
				LCD1602_writedata('0');
				LCD1602_writedata('x');
				for(i=length;i>0;i--)
				{
					T=(num/get16_power(i-1))%16;
					if(T>=10)
					{
						T=T+0x07;
						LCD1602_writedata(T+0x30);
					}
					if(T<10)
					{
						LCD1602_writedata((num/get16_power(i-1))%16+0x30);
					}
				}
				break;
		}
	}
}



void LCD_showbinnum(unsigned char r,unsigned char c,unsigned int num,unsigned char length)
{
	unsigned char i;
	if(r<=2&&c<=16)
	{
		switch (r)
		{
			case 1:
				LCD1602_writecommand(0x80+c-1);
				for(i=length;i>0;i--)
				{
					LCD1602_writedata((num/get2_power(i-1))%2+0x30);
				}
				break;
			case 2:
				LCD1602_writecommand(0x80+0x40+c-1);
				for(i=length;i>0;i--)
				{
					LCD1602_writedata((num/get2_power(i-1))%2+0x30);
				}
				break;
		}
	}
}