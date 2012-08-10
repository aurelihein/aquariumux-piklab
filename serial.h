/**
 * \file serial.h
 * \brief Serial Api for compiling with SDCC
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
// SPBRG value for FOSC 4MHz
#define B1200_4		0,51
#define B2400_4		0,25
#define B9600_4		1,25
#define B19200_4	1,12

// SPBRG value for FOSC 10 MHz

#define B1200_10         0,129
#define B2400_10         0,64
#define B9600_10         1,64
#define B19200_10        1,32
#define B38400_10        1,16

// SPBRG value for FOSC 20 MHz

#define B2400_20         0,129
#define B9600_20         1,129
#define B19200_20        1,64
#define B38400_20        1,32

// SPBRG value for FOSC 40 MHz

#define B9600_40         0,64
#define B19200_40        1,129
#define B38400_40        1,64
#define B56000_40        1,44
#define B57600_40        1,42
#define B115200_40       1,21

void serial_init(unsigned char setbrgh,unsigned char divider);
void serial_enable_interrupt(void);
void serial_putch(char c);
void serial_puts(const char *s);
void serial_interrupt_getch(const char c);
void serial_clear_received_buffer(void);
const char * serial_get_received_buffer(void);