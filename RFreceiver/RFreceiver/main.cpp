/*
 * RFreceiver.cpp
 *
 * Created: 12-06-2018 13:57:12
 * Author : sachin mahadevjadhav
 */ 
#include <avr/io.h>
#include "RF24.h"
RF24 radio(9, 10); // CE, CSN
//uint64_t pipes[3] = {0xF0F0F0F0E1LL,0xF0F0F0F0E2LL,0xF0F0F0F0E3LL };
const byte address[6] = "00001"; //5 Byte address of nrf device	
unsigned char count=1;
unsigned char p=0;
int main(void)
{ 
	unsigned char status1;
	UART_Init(9600);	 
	radio.begin();	 
	//radio.openWritingPipe(address);// transmitter address
	radio.openReadingPipe(0,address);// receiver address must be same as transmitter 
	radio.setPALevel(RF24_PA_MAX);// 0dBm power level
	radio.setDataRate(RF24_250KBPS);
	//radio.stopListening();//make radio  transmitter
	radio.startListening();
		//status1 = radio.read_register(NRF_CONFIG);
		//UART_Print_Num(status1);
	while (1)
	{  
		// status1 = radio.read_register(NRF_STATUS);
		//UART_Print_Num(status1);
		 unsigned char pipenum = 0;
		// UART_Printfln("JUST TESt");
	  // code for receiver		
			
		//status1= radio.read_register(RF_SETUP);
		 //UART_Print_Num(status1);
		while(radio.available(&pipenum))
	//	if (radio.available())
		 {
			 char text[32] = "";
			 radio.read(&text, sizeof(text));
			 UART_Printfln(text);
			 UART_Printf("Packet count:");
			 UART_Print_Num(count);
			 UART_Printf("Pipe Number:");
			 UART_Print_Num(pipenum);
			 count++;
			 p=radio.getPALevel();
			 UART_Printf("Power Level:");
			 UART_Print_Num(p);
		 }//if end
		// _delay_ms(1000);
		 // status1 = radio.read_register(FIFO_STATUS);
		 // UART_Print_Num(status1);
		 
		 // code for transmitter
		 //const char text[] = "Hello";
		 
		   //UART_Transmit('\n');
		/* if(radio.write(&text, sizeof(text))== true)
		  {
			  UART_Printfln("sent.");
		  }
		_delay_ms(1000);*/
	}// while 1 loop ends here
}//main ends here 

