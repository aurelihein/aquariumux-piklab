/* ----------------------------------------------------------------------- */
/* Fichier source modèle généré par Piklab */
#include <pic16f877a.h>
#include "lcd.h"
#include "asmdelay.h"
#include "serial.h"
#include "aquarium.h"

/* ----------------------------------------------------------------------- */
/* Bits de configuration: adapté à votre dispositif et à vos besoins */
typedef unsigned int word;
word at 0x2007 CONFIG = _HS_OSC & _WDT_OFF & _PWRTE_OFF & _BODEN_OFF & _LVP_OFF & _CPD_OFF & _WRT_OFF & _DEBUG_OFF & _CP_OFF;


//#define TEST	(1)

volatile char got_interrupt = 0;

void Intr() interrupt 0 {
	got_interrupt = 1;
	
	//if RCIF clear the RX interrupt
	if(RCIF)
	{
		serial_interrupt_getch(RCREG);
		RCREG = 0;
	}
	if(TMR0IF)
		TMR0IF = 0;
}

void main() {
  
  
    /* << insérer le code >> */
	unsigned char value;
/*
	NOT_RBPU=0;
	T2CON=0x7f;
	GIE = 1;
	PEIE = 1;
	//INTCON=0xc0;
	PIR1 = 0;
	PIE1 = 2;
	PR2 = 200;
*/
	PORTA = 0;
	TRISA = 0xF1;
	TRISB = 0x00;
	TRISD = 0x00;
	//désactive la convertion analogique
	ADCON0 = 0b00000000;
	ADCON1 = 0x0e;

	//interrupt timer0 //RA4
	TMR0IE = 1;
	TMR0 = 0xff;

	RA1 = RA2 = RA3 = 0;
	PORTB = 0x07;
	PORTC = 0x00;
	PORTD = 0x00;

	lcd_init();
	serial_init(B9600_4);
	serial_enable_interrupt();


	PEIE=1;		// enable peripheral interrupts
	GIE = 1;

	lcd_goto_1line();
	lcd_puts("Aquariumux v1.0");
	serial_puts("\r\n");
	serial_puts("**************************************************************\r\n");
	serial_puts("* Aquariumux v0.9 by Aurelien BOUIN =>http://www.bouinux.com *\r\n");
	serial_puts("**************************************************************\r\n");
	
	init_aquarium_state();
	update_output_cycle_remplissage();
	update_output_cycle_vidage();
	while(1)
	{
#ifdef	TEST
		add_cycle();
#endif
		cycle_remplissage();
		cycle_vidage();
		delay_a_s();
		incremente_tempo();
	}
	
#if 0
	while(1)
	{
		if(got_interrupt)
		{
			lcd_clear();
			lcd_goto_1line();
			lcd_puts(serial_get_received_buffer());
			serial_puts("[");
			serial_puts(serial_get_received_buffer());
			serial_puts("]");
			got_interrupt = 0;
		}
		//lcd_goto_1line();
		//lcd_puts("1234567890123456");
		PORTB = 0x05;
		delay_a_s();
		//lcd_goto_1line();
		//lcd_puts("ABCDEFGHIJKLMNOP");
		PORTB = 0x0a;
		delay_a_s();
	}
#endif
}
