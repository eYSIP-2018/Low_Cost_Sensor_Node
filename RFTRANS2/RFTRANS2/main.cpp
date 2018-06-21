/*
 * RFTRANS2.cpp
 *
 * Created: 19-06-2018 13:08:29
 * Author : sachin mahadevjadhav
 */ 
#include <avr/io.h>
#include "RF24.h"
RF24 radio(9, 10); // CE, CSN object for nRF24L01+
const uint64_t pipes[3] = {0xF0F0F0F0E1LL,0xF0F0F0F0E2LL,0xF0F0F0F0E3LL }; // address for diffrent pipes
//const byte address[6] = "00001"; //5 Byte address of nrf device	
unsigned char count=1;// for packet count
unsigned char p=0;// variable for power level
char data[10] = {"EYSIP2018"};
//char Ntime[3] = {"10"};//default value 
int main(void)
{ 
	unsigned char status1;//to read a NRF24L01 particular register using SPI
	UART_Init(9600);	 
	radio.begin();	 
	radio.setDataRate(RF24_250KBPS);
	radio.openWritingPipe(pipes[2]);// transmitter address for pipe 2
	//radio.setRetries(8,15);
	radio.stopListening();//make radio  transmitter
		while (1)
		{
			// code for transmitter
			// function to read modify data string i.e, read sensors data
			while (radio.write(data, sizeof(data)) != true)	{}
				sei();
				radio.powerDown();//sleep nrf24l01+
				power_down(20);//sleep mcu
				radio.powerUp();
			//radio.openReadingPipe(2,pipes[2]);
			//radio.startListening();// make receiver to get local time count from hub
			//while(radio.available()!= true){}//wait till data is not received
			//radio.read(&Ntime, sizeof(Ntime));
			//// _delay_ms(500);
			//sei();//enable global interrupts
			////if (Ntime[0]=='2')
			//power_down(20);
			////else
			////power_down(10);
			//radio.openWritingPipe(pipes[2]);// transmitter address for pipe 1
			//radio.stopListening();//make it transmitter
		}// while 1 loop ends here
}//main ends here 





