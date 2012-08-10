/**
 * \file lcd.h
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

void test_lcd(void);

/* write a byte to the LCD in 4 bit mode */

void lcd_write(unsigned char);

/* Clear and home the LCD */

void lcd_clear(void);
/* Clear and home the LCD */

void lcd_home(void);

/* write a string of characters to the LCD */

void lcd_puts(const char * s);

/* Go to the specified position */

void lcd_goto(unsigned char pos);
	
/* intialize the LCD - call before anything else */

void lcd_init(void);

void lcd_putch(char);

void lcd_goto_1line(void);

void lcd_goto_2line(void);
/*	Set the cursor position */

const char *long_into_char(long entry);
#define	lcd_cursor(x)	lcd_write(((x)&0x7F)|0x80)
