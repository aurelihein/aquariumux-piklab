/**
 * \file serial.c
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

#include <pic16f877a.h>
#include "serial.h"


#ifndef SERIAL_BUFFER_SIZE
#define SERIAL_BUFFER_SIZE	(16)
#endif
volatile unsigned char pbuffer = 0;
volatile char ring_buffer[SERIAL_BUFFER_SIZE];

/**
 * \brief Init the serial as 9600bauds 8bits no parity 1 stop
 * \param setbrgh Set the bit High speed for the UART
 * \param divider Set the divider value
 */
void serial_init(unsigned char setbrgh,unsigned char divider)
{
	TXSTA = 0b10100100;
	BRGH=setbrgh;			// set BRGH bit
	SPBRG=divider;			// set UART speed SPBRG
	RCSTA=0x90;			// set RCEN and SPEN
	serial_clear_received_buffer();
}

/**
 * \brief Enable the interrupt on the serial port
 */
void serial_enable_interrupt(void)
{
	RCIE=1;		// enable interrupt on RX
}

/**
 * \brief write a caracter of chars to the serial interface
 * \param c is the char to write 
 */
void serial_putch(char c)
{
	while(!TRMT);
		TXREG = c;
}

/**
 * \brief write a string of chars to the serial interface
 * \param s is the string to write 
 */
void serial_puts(const char *s)
{
	while(*s)
		serial_putch(*s++);	
}

/**
 * \brief handle the reception of a char from interrupt
 * \param s is the string to write 
 */
void serial_interrupt_getch(const char c)
{
	ring_buffer[pbuffer] = c;
	pbuffer++;
	if(pbuffer >= SERIAL_BUFFER_SIZE)
		pbuffer = 0;
}

/**
 * \brief Get last serial buffer
 * \param s is the string to write 
 */
void serial_clear_received_buffer(void)
{
	unsigned char i;
	for(i = 0; i < SERIAL_BUFFER_SIZE; i++)
		ring_buffer[i]='0';
	pbuffer = 0;
	
}
/**
 * \brief Get last serial buffer
 * \param s is the string to write 
 */
const char * serial_get_received_buffer(void)
{
#if 0
	unsigned char i,j,not_started=1;
	char temp[SERIAL_BUFFER_SIZE+1];
	temp[SERIAL_BUFFER_SIZE] = 0;


	for(i = 0, j = pbuffer; i < SERIAL_BUFFER_SIZE; i++, j++)
	{
		if(j >= SERIAL_BUFFER_SIZE)
			j = 0;
		if(!ring_buffer[j])
			if(not_started)
				continue;
			else
				break;
		not_started = 0;
		temp[i] = ring_buffer[j];
	}
	return temp;
#else
	return ring_buffer;
#endif
}	


