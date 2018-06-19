

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

#define F_CPU 8000000UL   // crystal frequency
#define __DELAY_BACKWARD_COMPATIBLE__  
/*to remove delay error _delay_us expects a constatnt.*/
#include <util/delay.h>
#include <avr/pgmspace.h>
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))

#ifndef GPIO2_H_
#define GPIO2_H_
// macros for pin names on atmega328p
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
#endif /* GPIO2_H_ */