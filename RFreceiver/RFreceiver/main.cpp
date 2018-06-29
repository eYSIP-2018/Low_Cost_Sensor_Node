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
//const byte address[6] = "00001"; //5 Byte address of nrf device
//const byte addr3 = 3;	
unsigned char count=1;// for packet count
unsigned char p=0;// variable for power level
//volatile unsigned char flag=0;
//char data0[12] = ""; 
//char data1[12] = "";
//char data2[12] = "";
//char data3[12] = "";
// array to collect sensor nodes data
int main(void)
{ 
	byte p1=0,p2=0,p3=0,p4=0;
	/// initilazation setup function in arduino
	unsigned char status1;//to read a NRF24L01 particular register using SPI
	UART_Init();	 
	radio.begin();
	Set_pin(13,OUT);
	radio.setDataRate(RF24_250KBPS);
	radio.setPALevel(RF24_PA_MAX);// 0dBm power level	
	//radio.openReadingPipe(0,pipes[0]);// receiver address must be same as transmitter
	radio.openReadingPipe(1,pipes[1]);// receiver address must be same as transmitter
	radio.openReadingPipe(2,pipes[2]);// receiver address must be same as transmitter 
	radio.openReadingPipe(3,pipes[3]);// receiver address must be same as transmitter
	radio.openReadingPipe(4,pipes[4]);// receiver address must be same as transmitter
	radio.startListening();// make radio Receiver
	// char data[] = "";
	/// the code which runs continuously
	while (1)
	{  
		 unsigned char pipenum=0;//to store number of particular pipe
		byte text[4] = "";// to store received data
		 sei();//enable global interrupt
		 while (radio.available(&pipenum))
		 {	
			radio.read(text, sizeof(text));
			text[3] = (byte)pipenum;
			//UART_Printf("Pipe NUM:");
			//UART_Print_Num(pipenum);
			//UART_Print_Byte(text);
			
			//UART_Printf(text);
		//if end
		 //data[0]=pipenum;
		 //strcat(data,text);
		 //UART_Printfln(data);
		//while(pipenum)
		//{
		switch (pipenum)
		{
			case 1:
				memcpy(sen1,text,4);
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
				//UART_Print_Byte(sen4);
				p4=1;
				break;
			default :
				UART_Printf("Nopipe");
			}
		}
		// check data of all node recevied
		if(p1&&p2&&p2&&p3&&p4)
		{
			//UART_Printf("sending");
			Write_Digital(13,high);
			_delay_ms(1000);
			Write_Digital(13,low);
			esp_wakeup();
			 esp_send();
				//UART_Print_Byte(sen1);
				//UART_Print_Byte(sen2);
				//UART_Print_Byte(sen3);
				//UART_Print_Byte(sen4);
			p1=0;p2=0;p3=0;p4=0;
			//UART_Printf("END");
		}
	//	}
	}// while 1 loop ends here
}//main ends here 

