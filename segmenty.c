#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include "segmenty.h"

volatile int8_t data[3]={0, 0, 0};

uint8_t cyfry[11]= {
	 0b00000011,			//0
	 0b10011111,			//1
	 0b00100101,			//2
	 0b00001101,			//3
	 0b10011001,			//4
	 0b01001001,			//5
	 0b01000001,			//6
	 0b00011111,			//7
	 0b00000001,			//8
	 0b00001001,			//9
	0xFF};	      	//puste
     
void segmenty_init()
{
	DDR(PORT_SEG_A) |= (1<<SEG_A);		//wszystkie segmenty jako wyjscia
	DDR(PORT_SEG_B) |= (1<<SEG_B);
	DDR(PORT_SEG_C) |= (1<<SEG_C);
	DDR(PORT_SEG_D) |= (1<<SEG_D);
	DDR(PORT_SEG_E) |= (1<<SEG_E);
	DDR(PORT_SEG_F) |= (1<<SEG_F);
	DDR(PORT_SEG_G) |= (1<<SEG_G);
	DDR(PORT_SEG_DOT) |= (1<<SEG_DOT);

	PORT(PORT_SEG_A) |= (1<<SEG_A);		//zgaszenie wszystkich segmentow
	PORT(PORT_SEG_B) |= (1<<SEG_B);
	PORT(PORT_SEG_C) |= (1<<SEG_C);
	PORT(PORT_SEG_D) |= (1<<SEG_D);
	PORT(PORT_SEG_E) |= (1<<SEG_E);
	PORT(PORT_SEG_F) |= (1<<SEG_F);
	PORT(PORT_SEG_G) |= (1<<SEG_G);
	PORT(PORT_SEG_DOT) |= (1<<SEG_DOT);

	DDR(PORT_ANODA_1) |= (1<<ANODA_1);	//wszystkie wyswietlacze jako wyjscia
	DDR(PORT_ANODA_2) |= (1<<ANODA_2);
	DDR(PORT_ANODA_3) |= (1<<ANODA_3);
	//DDR(PORT_ANODA_4) |= (1<<ANODA_4);

	PORT(PORT_ANODA_1) |= (1<<ANODA_1);	//zgaszenie wyswietlaczy
	PORT(PORT_ANODA_2) |= (1<<ANODA_2);
	PORT(PORT_ANODA_3) |= (1<<ANODA_3);
	//PORT(PORT_ANODA_4) |= (1<<ANODA_4);
}

ISR(TIMER0_COMP_vect)
{	
	uint8_t i;
	static uint8_t nr = 1;		//nr aktualnie wyswietlanego wyswietlacza

	if (nr == 1)
	{
		PORT(PORT_ANODA_3) |= (1<<ANODA_3);		//zgaszenie poprzedniego
		PORT(PORT_ANODA_1) &= ~(1<<ANODA_1);	//zapalenie nastepnego wyswietlacza
	}
	if (nr == 2)
	{
		PORT(PORT_ANODA_1) |= (1<<ANODA_1);	
		PORT(PORT_ANODA_2) &= ~(1<<ANODA_2);	
	}
	if (nr == 3)
	{
		PORT(PORT_ANODA_2) |= (1<<ANODA_2);	
		PORT(PORT_ANODA_3) &= ~(1<<ANODA_3);	
	}
	/*if (nr == 4)
	{
		PORT(PORT_ANODA_3) |= (1<<ANODA_3);	
		PORT(PORT_ANODA_4) &= ~(1<<ANODA_4);	
	}*/

	for (i=0; i<3; ++i)
	{
		if ((i+1) == nr)
		{
			if (cyfry[data[i]] & (1<<7)) 	PORT(PORT_SEG_A)|=(1<<SEG_A);
				else PORT(PORT_SEG_A) &= ~(1<<SEG_A);
			if (cyfry[data[i]] & (1<<6)) 	PORT(PORT_SEG_B)|=(1<<SEG_B);
				else PORT(PORT_SEG_B) &= ~(1<<SEG_B);
			if (cyfry[data[i]] & (1<<5)) 	PORT(PORT_SEG_C)|=(1<<SEG_C);
				else PORT(PORT_SEG_C) &= ~(1<<SEG_C);
			if (cyfry[data[i]] & (1<<4)) 	PORT(PORT_SEG_D)|=(1<<SEG_D);
				else PORT(PORT_SEG_D) &= ~(1<<SEG_D);
			if (cyfry[data[i]] & (1<<3)) 	PORT(PORT_SEG_E)|=(1<<SEG_E);
				else PORT(PORT_SEG_E) &= ~(1<<SEG_E);
			if (cyfry[data[i]] & (1<<2)) 	PORT(PORT_SEG_F)|=(1<<SEG_F);
				else PORT(PORT_SEG_F) &= ~(1<<SEG_F);
			if (cyfry[data[i]] & (1<<1)) 	PORT(PORT_SEG_G)|=(1<<SEG_G);
				else PORT(PORT_SEG_G) &= ~(1<<SEG_G);
			if (cyfry[data[i]] & (1<<0)) 	PORT(PORT_SEG_DOT)|=(1<<SEG_DOT);
				else PORT(PORT_SEG_DOT) &= ~(1<<SEG_DOT);
		}
	}
	

	if (++nr == 4) nr = 1;
}

void timer_on()
{	//timer0
	TCCR0 |= (1<<WGM01);	//CTC
	TCCR0 |= (1<<CS02)|(1<<CS00);	//1024
	OCR0 = 104;	//150hz
	TIMSK |= (1<<OCIE0);
}

