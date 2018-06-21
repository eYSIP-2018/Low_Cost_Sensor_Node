/*
 * RFreceiver.cpp
 *
 * Created: 12-06-2018 13:57:12
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
volatile unsigned char flg=0;
//char data0[12] = ""; 
//char data1[12] = "";
//char data2[12] = "";
//char data3[12] = "";
int main(void)
{ 
	/// initilazation setup function in arduino
	unsigned char status1;//to read a NRF24L01 particular register using SPI
	UART_Init(9600);	 
	radio.begin();
	radio.setDataRate(RF24_250KBPS);
	radio.setPALevel(RF24_PA_MAX);// 0dBm power level	
	//radio.openReadingPipe(0,pipes[0]);// receiver address must be same as transmitter
	radio.openReadingPipe(1,pipes[1]);// receiver address must be same as transmitter
	radio.openReadingPipe(2,pipes[2]);// receiver address must be same as transmitter 
	//radio.openReadingPipe(3,pipes[3]);// receiver address must be same as transmitter
	radio.startListening();// make radio Receiver
	// char data[] = "";
	while (1)
	{  
		 unsigned char pipenum=0;//to store number of particular pipe
		byte text[5] = "";// to store received data
		 sei();//enable global interrupt
		 while (radio.available(&pipenum))
		 {	
			
			radio.read(text, sizeof(text));
			text[3] = pipenum;
			UART_Printf("Pipe NUM:");
			UART_Print_Num(pipenum);
			UART_Print_Byte(text);
			
			//UART_Printf(text);
		 }//if end
		 //data[0]=pipenum;
		 //strcat(data,text);
		 //UART_Printfln(data);
		/*while(pipenum)
		{
		switch (pipenum)
		{
			case 0:
				memcpy(data0,data,11);
				break;
			case 1:
				memcpy(data0,data,11);
				break;
			case 2:
				memcpy(data0,data,11);
				break;
			case 3:
				memcpy(data0,data,11);
				break;
		}
		}*/
	}// while 1 loop ends here
}//main ends here 

