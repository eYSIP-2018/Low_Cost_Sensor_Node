/*
 * RFreceiver.cpp
 *
 * Created: 12-06-2018 13:57:12
 * Author : sachin mahadevjadhav
 */ 
#include <avr/io.h>
#include "RF24.h"

RF24 radio(9, 10); // CE, CSN
const uint64_t pipes[5] = {0xF0F0F0F0E1LL,0xF0F0F0F0E2LL,0xF0F0F0F0E3LL,0xF0F0F0F0E4LL,0xF0F0F0F0E5LL}; // address for diffrent pipes
unsigned char count=1;// for packet count
unsigned char p=0;// variable for power level
// flags for receiption of data of each pipe
byte p1=0;
byte p2=0;
byte p3=0;
byte p4=0;
int main(void)
{ 
	cli();// disable global interrupt
	//power to nrf start mosfet 
	mosfet_on();
	/// initialization same as setup function in arduino
	unsigned char status1;//to read a NRF24L01 particular register using SPI
	UART_Init();	 
	radio.begin();
	radio.setDataRate(RF24_250KBPS); // set data rate 250 kbps
	radio.setPALevel(RF24_PA_MAX);// 0dBm power level	
	// Open pipes for all tansmitter nodes with their pipe number and address
	radio.openReadingPipe(1,pipes[1]);// receiver address must be same as transmitter
	radio.openReadingPipe(2,pipes[2]);
	radio.openReadingPipe(3,pipes[3]);
	radio.openReadingPipe(4,pipes[4]);
	radio.startListening();// make radio Receiver
	// char data[] = "";
	/// the code which runs continuously
	sei();
	while (1)
	{  
	 unsigned char pipenum=0;//to store number of particular pipe
	 byte text[4] = "";// to store received data
		 while (radio.available(&pipenum))
		 {	
			radio.read(&text, sizeof(text));
			text[3] = (byte)pipenum;//last byte in data packet is pipe number
			// just for debugging
			// print data on serial monitor
			//UART_Printf("Pipe NUM:");
			//UART_Print_Num(pipenum);
			//UART_Print_Byte(text);
		 }
	// Store received data on corresponding array of each node
		switch (pipenum)
		{
			case 1:
				// copy received data into a byte array 
				memcpy(sen1,text,4);//dest,source,no of bytes
				//UART_Print_Byte(sen1);
				p1=1;
				break;
			case 2:
				memcpy(sen2,text,4);
				//UART_Print_Byte(sen2);
				p2=1;
				break;
			case 3:
				memcpy(sen3,text,4);
				//UART_Print_Byte(sen3);
				p3=1;
				break;
			case 4:
			memcpy(sen4,text,4);
				//UART_Print_Byte(sen3);
				p4=1;
				break;
			default :
				UART_Printf("Nopipe");
			}
		
		}
		// check data of all node recevied
		if(p1&&p2&&p3&&p4)
		{
			// just for debugging to print data on Serial monitor
			//UART_Print_Byte(sen1);
			//UART_Print_Byte(sen2);
			//UART_Print_Byte(sen3);
			 esp_send();// Send data seriallly to ESP32
			 // make flag 0 for next data receiption
			p1=0;p2=0;
			p3=0;p4=0;

	}// while 1 loop ends here	
}//main ends here 

