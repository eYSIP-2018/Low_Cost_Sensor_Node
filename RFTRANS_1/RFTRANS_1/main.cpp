/*
 * RFTRANS_1.cpp
 *
 * Created: 19-06-2018 12:17:20
 * Author : sachin mahadevjadhav
 */ 
#include <avr/io.h>
#include "RF24.h"

RF24 radio(9, 10); // CE, CSN
const uint64_t pipes[4] = {0xF0F0F0F0E1LL,0xF0F0F0F0E2LL,0xF0F0F0F0E3LL,0xF0F0F0F0E5LL}; // address for diffrent pipes
//const byte address[6] = "00001"; //5 Byte address of nrf device	
//const byte addr3 = 3;
unsigned char count=1;// for packet count
unsigned char p=0;// variable for power level
char data[9] = {"EYRC2017"};
int main(void)
{ 
	unsigned char status1;//to read a NRF24L01 particular register using SPI
	UART_Init(9600);	 
	radio.begin();	 
	radio.openWritingPipe(pipes[3]);// transmitter address for pipe 1
	radio.setDataRate(RF24_250KBPS);
	//radio.setRetries(12,15);
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



