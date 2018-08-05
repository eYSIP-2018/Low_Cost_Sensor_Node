
/*
 * gpio2.h
 *
 * Created: 11-06-2018 17:03:17
 *  Author: sachin mahadevjadhav
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL   // crystal frequency attached to controler on board
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
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
// Below variable used in main function of transmitter node
extern byte data[4];// to store sensor data 
// functions Related to general purpose input output
void Set_pin (unsigned int, unsigned int);
void Write_Digital (unsigned int, bool );
void mosfet_on();// turns mosfet on to give supply to NRF and ADC channels
void mosfet_off();// turns mosfet off to give supply to NRF and ADC channels
// Functions For UART Communicaton
void UART_Init();
void UART_Transmit(unsigned char);
char UART_Available();
char UART_Read();
void UART_Printfln(const char *);
void UART_Printf(const char *);
void UART_Print_Num(unsigned int );
void UART_Print_Numchar(unsigned char );
void UART_Print_Byte(byte*);
void UART_TransmitByte(byte );
// Functions related to timer0 .
// this is used by millis function  to get runtime execution time in milliseconds
void timer0_init (void);
unsigned int millis(void);
// Functions related to ADC 
// To read a sensor value on a particular channel 
unsigned int adcinit(int);
void adc_init();
unsigned int adc_read(unsigned char );
// API for power down mode for given time
void power_down (unsigned int );//for atmega328p
// API for collecting sensors data 
void getdata();
uint8_t get_batt_voltage();//Returns battery voltage
uint8_t get_temp(int ch);// returns temperature value in integar
uint8_t get_soil_moisture();// returns soil moisture content in percentage
#endif /* GPIO2_H_ */