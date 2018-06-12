/*
 * gpio2.c
 *
 * Created: 11-06-2018 17:04:20
 *  Author: sachin mahadevjadhav
 */ 
#include "gpio2.h"
volatile unsigned int cnt=0;//for timer counter delays and millis

/* To set a particular pin as input (IN)
 *  or output (OUT) .
 *  e.g Set_pin(13,OUT);
 */
//void Set_pin(unsigned char , unsigned char);
/* To set a particular output pin as a high or low by giving pin number and value.
 *  e.g. Write_Digital(13,high);
 */
//void Write_Digital (unsigned char , unsigned char );
//void UART_Init(uint32_t ); // initilzation of uart
///////////////////////////
void UART_Init(uint32_t v_baudRate_u32)
{
  UCSR0B = 0x00;
  UCSR0A = 0x00; 
  UCSR0C|= (1<<UCSZ1) | (1<<UCSZ0)|(1<< USBS0);   // Asynchronous mode 8-bit data and 1-stop bit                                 // Clear the UASRT status register
  UBRR0L = 51; // set baud rate 9600(51) ,4800(103),2400(206) for serial transmission with external crystal oscilator at 8.0 MHz 
  UBRR0H = 0;
  UCSR0B |= (1<<RXEN) | (1<<TXEN);                  // Enable Receiver and Transmitter
}
//////////////
void UART_Transmit(unsigned char data )
{
 UCSR0A = 1<<TXC0;
/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) );
/* Put data into buffer, sends the data */
UDR0 = data;
while (!(UCSR0A & (1<<TXC0)));
}
/////////////////

void UART_Printfln(const char *text)
{
  unsigned char i=0;
  while (!(*(text+i) == '\0'))
  {
    UART_Transmit(*(text+i));
    i++;
  } 
  UART_Transmit('\n');
}
//////////
void UART_Printf(const char *text)
{
  unsigned char i=0;
  while (!(*(text+i) =='\0'))
  {
    UART_Transmit(*(text+i));
    i++;
  } 
}
/// to print number
void UART_Print_Num(unsigned int n)
{ 
	unsigned char ch=0;
	ch= n/10000+0x30;
	UART_Transmit(ch);
	n=n%10000;
	ch=n/1000+0x30;
	UART_Transmit(ch);
	n=n%1000;
	ch=n/100+0x30;
    UART_Transmit(ch);
	n=n%100;
	ch=n/10+0x30;
	UART_Transmit(ch);
	ch=(n%10)+0x30;
    UART_Transmit(ch);	
    UART_Transmit('\n');	
}
///////////
void Set_pin (unsigned int num, unsigned int dir )
{
	if (dir == OUT )
	{  if (num >=8 )
		DDRB |= (1<<(num-8));
		else
		DDRD |= (1<<num);
	}
	else
	{
		if (num >=8 )
		DDRB |= (0<<(num-8));
		else
		DDRD |= (0<<num);
	}
}
/////////////
void Write_Digital (unsigned int num, bool value)
{
   //cli();
    if (value  == high )
   {  
    if (num >= 8 )
           PORTB = (1<<(num-8));
    else 
          PORTD |= (1<<num);
   }
   else 
    { 
      if (num >=8 )
           PORTB &= ~(1<<(num-8));
      else 
          PORTD &= ~(1<<num);
    }
   // sei();
}
////timer0 in CTC mode with interrupt 
void timer0_init ()
{
	//set timer0 interrupt at 1kHz
	TCCR0A = 0;
	TCCR0B = 0;
	TCNT0  = 0;
	// set compare match register for 1khz increments
	OCR0A = 124;// = (8*10^6) / (1000*64) - 1 (must be <256)
	 // turn on CTC mode
	 TCCR0A |= (1 << WGM01);
	 // Set CS01 and CS00 bits for 64 prescaler
	 TCCR0B |= (1 << CS01) | (1 << CS00);
	 // enable timer compare interrupt
	 TIMSK0 |= (1 << OCIE0A);
}
// ISR for timer 0
ISR(TIMER0_COMPA_vect)
{
	cnt++;
}
//
// returns millis count value
unsigned int millis()
{
	//timer0_init();
	return cnt;
}
