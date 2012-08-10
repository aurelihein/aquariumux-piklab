/**
 * \file asmdelay.c
 * \brief Delay Assembler coded for compiling with SDCC
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
#include "asmdelay.h"


unsigned char vara = 0,varb = 0,varc = 0;

void delay_a_s(void)
{
_asm

temporisation_1_sec:
	movlw	D'6'
	movwf	_varc
temporisation_1_sec_boucle:
	call	sous_temporisation_1_sec
	decfsz	_varc,1
	goto	temporisation_1_sec_boucle
	return

sous_temporisation_1_sec:
	movlw	D'217'
	movwf	_varb
	movlw	D'111'
	movwf	_vara
sous_temporisation_1_sec_boucle:
	decfsz	_vara,1
	goto	sous_temporisation_1_sec_boucle
	decfsz	_varb,1
	goto	sous_temporisation_1_sec_boucle
	return
_endasm;
}

void delay_hundred_ms(void)
{
_asm
temporisation_hundred_ms:
	movlw	D'130'
	movwf	_varb
	movlw	D'221'
	movwf	_vara
temporisation_hundred_ms_boucle:
	decfsz	_vara,1
	goto	temporisation_hundred_ms_boucle
	decfsz	_varb,1
	goto	temporisation_hundred_ms_boucle
_endasm;
}


void delay_ten_ms(void)
{
_asm
temporisation_ten_msec:
	movlw	D'13'
	movwf	_varb
	movlw	D'251'
	movwf	_vara
temporisation_ten_msec_boucle:
	decfsz	_vara,1
	goto	temporisation_ten_msec_boucle
	decfsz	_varb,1
	goto	temporisation_ten_msec_boucle
_endasm;
}

void delay_one_ms(void)
{
_asm
	movlw	D'2'
	movwf	_varb
	movlw	D'74'
	movwf	_vara
temporisation_a_ms_boucle:
	decfsz	_vara,1
	goto	temporisation_a_ms_boucle
	decfsz	_varb,1
	goto	temporisation_a_ms_boucle
_endasm;
}

void DelayUs(unsigned char cnt)
{
	unsigned char i;
	for (i = 0; i < cnt; i++)
	{
		_asm
			nop
		_endasm;
	}
}

void DelayMs(unsigned char cnt)
{
	unsigned char i;
	for (i = 0; i < cnt; i++)
	{
		delay_one_ms();
	}		
}