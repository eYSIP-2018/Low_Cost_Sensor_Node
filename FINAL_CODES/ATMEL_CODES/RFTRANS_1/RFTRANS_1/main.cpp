/*
 * RFTRANS_1.cpp
 *
 * Created: 19-06-2018 12:17:20
 * Author : sachin mahadev jadhav
 */ 
#include <avr/io.h>
#include "RF24.h"
//for every diffrent transmitter  just change following macro to its node number
#define  NODE_NUMBER 1
// address for diffrent pipes numbers for transmission of data through diffrent pipes
const uint64_t pipes[5] = {0xF0F0F0F0E1LL,0xF0F0F0F0E2LL,0xF0F0F0F0E3LL,0xF0F0F0F0E4LL,0xF0F0F0F0E5LL}; 	
unsigned char count=1;//variable for packet count
unsigned char p=0;// variable for power level
byte data[4]="";	
unsigned int test=0;
RF24 radio(9, 10); // CE, CSN	
int main(void)
{ 
	cli();//disable global interrupt
	unsigned char status1=0;//to read a NRF24L01 particular register using SPI
	UART_Init();
	// Every time turn ON mosfet  before initialsing NRF24L01+
	mosfet_on();
	radio.begin();	 
	radio.openWritingPipe(pipes[NODE_NUMBER]);// transmitter address for pipe 1
	radio.setDataRate(RF24_250KBPS);// set 250 kbps speed for transmission
	// sets ARD(Auto Retransmission Delay) and ARC(Auto Retransmission count)
	//radio.setRetries(12,15);
	radio.stopListening();//make radio  transmitter	
	sei();//enable global interrupts
	
	while (1)
	{
		// collect data of all sensors 
		getdata();
		// send data with fixed ARD untill ACK is not received
		while(radio.write(data, sizeof(data))!=true){}
			 sei();//enable global interrupts
			 radio.powerDown(); 
			 // switch off mosfet before sleep
			 mosfet_off();// write 1 to ON P channel MOsfet(0ff mosfet)
			 //wait for 10 seconds just for testing insert power down delay here
			 _delay_ms(10000); 
			 
			// power_down(10);// put msu in sleep for given(10) minutes or seconds
			// turn on supply to NRF after waking up
			mosfet_on();
			radio.powerUp();//power up nrf
			radio.begin(); // initailaztion of NRF 
			radio.openWritingPipe(pipes[NODE_NUMBER]);// transmitter address for pipe number
			radio.setDataRate(RF24_250KBPS);// set data rate for transmission as 250kbps
			//radio.setRetries(12,15);// set diffrent ARD,ARC for each transmitter node
			radio.stopListening();//make radio  transmitter
			 
	}// while 1 ends here	
}//main ends here 


