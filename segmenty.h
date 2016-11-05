#ifndef segmenty_h
#define segmenty_h

#define PORT(x)		XPORT(x)
#define XPORT(x)	(PORT##x)

#define PIN(x)		XPIN(x)
#define XPIN(x)		(PIN##x)

#define DDR(x)		XDDR(x)
#define XDDR(x)		(DDR##x)

#define PORT_SEG_A		C
#define PORT_SEG_B		C
#define PORT_SEG_C		C
#define PORT_SEG_D		C
#define PORT_SEG_E		C
#define PORT_SEG_F		C
#define PORT_SEG_G		C
#define PORT_SEG_DOT	C

#define SEG_A			0	
#define SEG_B			1
#define SEG_C			2
#define SEG_D			3
#define SEG_E			4
#define SEG_F			5
#define SEG_G			6
#define SEG_DOT			7

#define PORT_ANODA_1	A		//podlaczenie 4 wyswietlaczy
#define PORT_ANODA_2	A
#define PORT_ANODA_3	A
//#define PORT_ANODA_4	A

#define ANODA_1			0
#define ANODA_2			1
#define ANODA_3			2
//#define ANODA_4			3

extern volatile int8_t data[3];

void segmenty_init();
void timer_on();

#endif
