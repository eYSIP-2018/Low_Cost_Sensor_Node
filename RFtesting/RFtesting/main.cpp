/*
 * RFtesting.cpp
 *
 * Created: 11-06-2018 14:22:07
 * Author : sachin mahadevjadhav
 */ 

#include <avr/io.h>


#include "RF24.h"

/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*
* by Dejan Nedelkovski, www.HowToMechatronics.com
*
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
unsigned count=0;
unsigned char p=0;
int main(void)
{
	Set_pin(1,OUT);

	UART_Init(9600);
	radio.begin();
	radio.openWritingPipe(address);
	radio.setPALevel(RF24_PA_MAX);
	//radio.setDataRate(RF24_250KBPS);
	radio.stopListening();
	
    while (1) 
    {
			//radio.powerUp();
			const char text[] = "Hello";
			radio.write(&text, sizeof(text));
			_delay_ms(1000);
			//radio.powerDown();
			_delay_ms(2000);
			count++;
			p=radio.getPALevel();
			UART_Printf("Power Level:");
			//UART_Print_Num(p);
			UART_Printf("Packet Count:");
			//UART_Print_Num(count);

		
		
    }
}

