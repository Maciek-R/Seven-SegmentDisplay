//Maciej Ruszczyk
//Licznik rewersyjny od 0 do 100
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "segmenty.h"

#define KEY_PIN_UP (1<<PD7)
#define KEY_PIN_DOWN (1<<PD6)

#define KEY_PIN_UP_DOWN (!(PIND & KEY_PIN_UP))
#define KEY_PIN_DOWN_DOWN (!(PIND & KEY_PIN_DOWN))

void obsluz ()
{
	_delay_ms(50);
		if (KEY_PIN_UP_DOWN)
		{
			if (++data[2] == 10) {++data[1]; data[2]=0;}
			if (data[1] == 10) {++data[0]; data[1]=0;}
			if (data[0] == 1 && data[2] == 1) {data[0]=data[1]=data[2]=0;}
		}

		if (KEY_PIN_DOWN_DOWN)
		{
			if (--data[2] < 0) {--data[1]; data[2]=9;}
			if (data[1] < 0) {--data[0]; data[1]=9;}
			if (data[0] < 0) {data[0]=1; data[1]=data[2]=0;}
		}
}

int main()
{
	DDRD &= ~(KEY_PIN_UP | KEY_PIN_DOWN);
	PORTD |= KEY_PIN_UP | KEY_PIN_DOWN;

	segmenty_init();
	timer_on();
	sei();


	while (1)
	{	
		if (KEY_PIN_UP_DOWN || KEY_PIN_DOWN_DOWN)
		{
			obsluz();
		}
	}

	return 0;
}
