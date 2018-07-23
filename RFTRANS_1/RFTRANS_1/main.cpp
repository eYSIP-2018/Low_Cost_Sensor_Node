/*
 * RFTRANS_1.cpp
 *
 * Created: 19-06-2018 12:17:20
 * Author : sachin mahadevjadhav
 */ 
#include <avr/io.h>
#include "RF24.h"
void getdata();
RF24 radio(9, 10); // CE, CSN
const uint64_t pipes[4] = {0xF0F0F0F0E1LL,0xF0F0F0F0E2LL,0xF0F0F0F0E3LL,0xF0F0F0F0E5LL}; // address for diffrent pipes
//const byte address[6] = "00001"; //5 Byte address of nrf device	
//const byte addr3 = 3;
unsigned char count=1;// for packet count
unsigned char p=0;// variable for power level
//char data[10] = {"EYRC2017S"};
byte data[4]="";	
char Ntime[3] = "";
int main(void)
{ 
	unsigned char status1;//to read a NRF24L01 particular register using SPI
	UART_Init(9600);	 
	radio.begin();	 
	radio.openWritingPipe(pipes[1]);// transmitter address for pipe 1
	radio.setDataRate(RF24_250KBPS);
	//radio.setRetries(12,15);
	radio.stopListening();//make radio  transmitter
	while (1)
	{
	 // code for transmitter
		// function to read modify data string i.e, read sensors data
		//unsigned char status=0;
		//status = radio.read_register(NRF_CONFIG);
		//UART_Print_Num(status);
	//	getdata();
		radio.write(data, sizeof(data));
		_delay_ms(2000);
			// sei();//enable global interrupts
			// radio.powerDown();
			// power_down(20);
		//	 radio.powerUp();
		 //radio.openReadingPipe(1,pipes[1]);
		 //radio.startListening();// make receiver to get local time count from hub
		 //while(radio.available()!= true){}//wait till data is not received
		 //radio.read(&Ntime, sizeof(Ntime)); 
		// UART_Printf(Ntime); 
		 // _delay_ms(500);
			//power_down(10);
			//radio.openWritingPipe(pipes[1]);// transmitter address for pipe 1
			//radio.stopListening();//make it transmitter
	}// while 1 loop ends here
}//main ends here 
/// function to collect data from sensor user can add data depending on number of sensors
void getdata()
{
	data[0] = 250;//battery voltage
	data[1] = 25;//temp value from temp sensor
	data[2] = 76;//humidity value from DHTsensor
}


