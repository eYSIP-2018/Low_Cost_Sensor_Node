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
		 radio.write(data, sizeof(data));
		  //{
			  //UART_Printfln("sent.");
			  //UART_Printf(data);
		  //}
		_delay_ms(10000);
	}// while 1 loop ends here
}//main ends here 





