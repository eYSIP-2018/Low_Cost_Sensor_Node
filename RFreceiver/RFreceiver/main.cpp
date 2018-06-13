/*
 * RFreceiver.cpp
 *
 * Created: 12-06-2018 13:57:12
 * Author : sachin mahadevjadhav
 */ 
#include <avr/io.h>
#include "RF24.h"

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
unsigned char count=0;
unsigned char p=0;
int main(void)
{
	UART_Init(9600);
	radio.begin();
	radio.openReadingPipe(0, address);
	//radio.setPALevel(RF24_PA_MAX);// 0dBm power level
	//radio.setDataRate(RF24_250KBPS);
	radio.startListening();
	
	while (1)
	{   // UART_Printfln("JUST TESt");
		 if (radio.available())
		 {
			 char text[32] = "";
			 radio.read(&text, sizeof(text));
			 UART_Printfln(text);
			 UART_Printf("Packet count:");
			 UART_Print_Num(count);
			 count++;
			 p=radio.getPALevel();
			 UART_Printf("Power Level:");
			 UART_Print_Num(p);
		 }//if end
		// _delay_ms(1000);
		 
	}// while 1 loop ends here
}//main ends here 

