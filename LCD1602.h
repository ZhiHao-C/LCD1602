#ifndef __LCD1602_H__
#define __LCD1602_H__

void LCD1602_writecommand(unsigned char command);
void LCD1602_writedata(unsigned char Data);
void LCD1602_Init();
void LCD1602_showchar(char r,char c,char Char);
void LCD1602_showstring(char r,char c,char *string);
void LCD_shownum(unsigned char r,unsigned char c,unsigned int num,unsigned char length);
unsigned char power(int x,int y);
void LCD_showsignednum(unsigned char r,unsigned char c, int num,unsigned char length);
void LCD_showhexnum(unsigned char r,unsigned char c,unsigned int num,unsigned char length);
void LCD_showbinnum(unsigned char r,unsigned char c,unsigned int num,unsigned char length);
#endif