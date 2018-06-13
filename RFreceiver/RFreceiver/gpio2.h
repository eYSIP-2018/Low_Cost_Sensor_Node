

#include <stdbool.h>
void Set_pin (unsigned int, unsigned int);
void Write_Digital (unsigned int, bool );
/*
 * gpio2.h
 *
 * Created: 11-06-2018 17:03:17
 *  Author: sachin mahadevjadhav
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdint.h>
#define F_CPU 8000000UL
#define __DELAY_BACKWARD_COMPATIBLE__  
/*to remove delay error _delay_us expects a constatnt.*/
#include <util/delay.h>
#include <avr/pgmspace.h>


#ifndef GPIO2_H_
#define GPIO2_H_

#define OUT 1
#define IN  0
#define LED 13
#define high 1
#define low  0
#define TXEN 3
#define RXEN 4
#define UCSZ0 1
#define UCSZ1 2
#define UDRE0 5
#define UCSRE0 6
#define USBS0  3
#define SS 10
#define MOSI 11
#define MISO 12
#define SCK 13

#define IF_SERIAL_DEBUG(x) ({x;})
typedef bool boolean;
typedef uint8_t byte;

void UART_Init(uint32_t);
void UART_Transmit(unsigned char);
void UART_Printfln(const char *);
void UART_Printf(const char *);
void UART_Print_Num(unsigned int );
void UART_Print_Numchar(unsigned char );
void timer0_init (void);
unsigned int millis(void);

// Main code

/*unsigned char flg =0;
int main()
{
  
 cli();
//set timer0 interrupt at 2kHz
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
  Set_pin(13, OUT); 
  UART_Init(9600);
  sei();
  
  while (1)
  {
    if ((cnt == 1000)&&(flg==0))
    {
     Write_Digital(13, high);
     cnt=0;
     flg=1;
     UART_Transmit('A');
    }  
    if ((cnt == 1000)&&(flg==1))
    {
     Write_Digital(13, low);
     cnt=0;
     flg=0;
      UART_Transmit('B');
    } 
    //UART_Printfln("SACHIN1234");
   
    //UART_Transmit ('\n');
  }
}
*/





#endif /* GPIO2_H_ */