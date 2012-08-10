/**
 * \file lcd.c
 * \brief LCD driving for compiling with SDCC
 * \author Aurelien BOUIN
 * \version 1.0.0
 * \date 18 june 2011
 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (C) 2011  Aurelien BOUIN (a_bouin@yahoo.fr)                  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  This program is free software; you can redistribute it and/or              *
 *  modify it under the terms of the GNU General Public License                *
 *  as published by the Free Software Foundation; either version 3             *
 *  of the License, or (at your option) any later version.                     *
 *                                                                             *
 *  This program is distributed in the hope that it will be useful,            *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 *  GNU General Public License for more details.                               *
 *                                                                             *
 *  You should have received a copy of the GNU General Public License          *
 *  along with this program; if not, write to the Free Software                *
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include	<stdio.h>
#include	<pic16f877a.h>
#include	"lcd.h"
//#include	"delay.h"
#include	"asmdelay.h"

#define DATA3	RD3
#define DATA2	RD2
#define DATA1	RD1
#define DATA0	RD0

#define LCD_RS	RA3
#define LCD_RW	RA2
#define LCD_EN	RA1

void lcd_change_data_port(unsigned char dataw)
{
	LCD_EN = 1;
	DATA3 = DATA2 = DATA1 = DATA0 = 0;
	if(dataw & 0x08)
		DATA3 = 1;
	if(dataw & 0x04)
		DATA2 = 1;
	if(dataw & 0x02)
		DATA1 = 1;
	if(dataw & 0x01)
		DATA0 = 1;
	LCD_EN = 0;
}

/* write a byte to the LCD in 4 bit mode */
void lcd_write(unsigned char c)
{
	lcd_change_data_port((c >> 4)&0x0f);
	DelayUs(40);
	lcd_change_data_port((c)&0x0f);
	DelayUs(40);
}

/* Clear and home the LCD */
void
lcd_clear(void)
{
	LCD_RS = 0;
	lcd_write(0x1);
	DelayMs(2);
}

/* cursor at home */
void lcd_home(void)
{
	LCD_RS = 0;
	lcd_write(0x2);
	DelayMs(2);
}

/* write one character to the LCD */
void lcd_putch(char c)
{
	LCD_RS = 1;		// write characters
	lcd_write(c);
}

/* write a string of chars to the LCD */
void lcd_puts(const char *s)
{
	while(*s)
		lcd_putch(*s++);	
}

/* Go to the specified position */
void lcd_goto(unsigned char pos)
{
	LCD_RS = 0;
	lcd_write(0x80+pos);
	DelayUs(40);
}

/* Go to the first line */
void lcd_goto_1line(void)
{
	lcd_goto(0);
}

/* Go to the second line */
void lcd_goto_2line(void)
{
	lcd_goto(0x40);
}

/* initialise the LCD - put into 4 bit mode */
void lcd_init(void)
{
	DelayMs(30);
	LCD_EN = 0;
	LCD_RW = 0;
	LCD_RS = 0;	// write control bytes
	DelayMs(15);

	lcd_change_data_port(0);
	DelayMs(5);
	lcd_change_data_port(1);
	DelayMs(5);
	lcd_change_data_port(0);
	DelayMs(5);
	lcd_change_data_port(0);
	DelayMs(5);
	lcd_change_data_port(1);
	DelayMs(5);
	lcd_change_data_port(3);
	DelayMs(5);
	lcd_change_data_port(3);
	DelayMs(5);
	lcd_change_data_port(3);
	DelayMs(5);
	lcd_change_data_port(2);
	DelayMs(5);
	lcd_write(0x28);
	lcd_write(0x0c);
	lcd_write(0x01);
	DelayMs(8);
	lcd_write(0x02);
	DelayMs(14);
	DelayMs(4);
	LCD_RS = 1;
	lcd_write(0x4e);
	DelayMs(1);

}

const char *long_into_char(long entry)
{
	char hex_value[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	char returned[5]={'0','0','0','0',0};
	returned[3] = hex_value[(entry & 0xf)];
	if(((entry >>4) & 0xf))
		returned[2] = hex_value[((entry >>4) & 0xf)];
	if(((entry >>8) & 0xf))
		returned[1] = hex_value[((entry >>8) & 0xf)];
	if(((entry >>12) & 0xf))
		returned[0] = hex_value[((entry >>12) & 0xf)];
	return returned;
}
