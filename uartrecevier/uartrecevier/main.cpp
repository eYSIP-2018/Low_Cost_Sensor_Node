/*
 * uartrecevier.cpp
 *
 * Created: 26-06-2018 12:24:45
 * Author : sachin mahadevjadhav
 */ 

#include <avr/io.h>
extern "C"
{
	#include "gpio2.h"
};
void esp_wakeup();//function to wakeup esp32
//default node data
byte sen1[]={25,75,34,1};//node data 1
byte sen2[]={35,85,33,2};
byte sen3[]={45,45,32,3};
byte sen4[]={55,45,31,4};
byte flg=1;//flag for sequence of node data
int main(void)
{
    /* Replace with your application code */
	char z=0;
	Set_pin(3,OUT);
	UART_Init();
    while (1) 
    {
    	//esp_wakeup();//wakeup esp 
	
		while(UART_Available())
		{
				
				z = UART_Read();
				//_delay_ms(100);
				//UART_Transmit(z);
			if ((z == 'C')&&(flg<5))
			{
				
				//send packet
				unsigned char i=0;
				//delay(1000);
				if (flg==1)
				{
					for (i=0;i<4;i++)
					{
						UART_TransmitByte(sen1[i]);
						//delay(1000);
					}	
						
				}//flg 1 end
				if (flg==2)
				{
					for (i=0;i<4;i++)
					{
						UART_TransmitByte(sen2[i]);
						//delay(1000);
					}
				}//flg 2 end
				if (flg==3)
				{
					for (i=0;i<4;i++)
					{
						UART_TransmitByte(sen3[i]);
						//delay(1000);
					}
				}//flg 3 end
				if (flg==4)
				{
					for (i=0;i<4;i++)
					{
						UART_TransmitByte(sen4[i]);
						//delay(1000);
					}
					flg=0;//reset flag to zero
				}//flg  4 end	
			flg++;
			}
			//ESP in sleep
			_delay_ms(10000);
		}
	}   
}
void esp_wakeup()
{
		// high low pulse on D3 pin
		Write_Digital(3,high);
		_delay_ms(100);
		Write_Digital(3,low);
}
void esp_send()
{
	
		esp_wakeup();//wakeup esp from sleep
		while(UART_Available())
		{ 
				z = UART_Read();
				//_delay_ms(100);
				//UART_Transmit(z);
			if ((z == 'C')&&(flg<5))
			{
				
				//send packet
				unsigned char i=0;
				//delay(1000);
				if (flg==1)
				{
					for (i=0;i<4;i++)
					{
						UART_TransmitByte(sen1[i]);
						//delay(1000);
					}	
						
				}//flg 1 end
				if (flg==2)
				{
					for (i=0;i<4;i++)
					{
						UART_TransmitByte(sen2[i]);
						//delay(1000);
					}
				}//flg 2 end
				if (flg==3)
				{
					for (i=0;i<4;i++)
					{
						UART_TransmitByte(sen3[i]);
						//delay(1000);
					}
				}//flg 3 end
				if (flg==4)
				{
					for (i=0;i<4;i++)
					{
						UART_TransmitByte(sen4[i]);
						//delay(1000);
					}
					flg=0;//reset flag to zero
				//	return 1; if function type byte  
				}//flg  4 end	
			  flg++;
			}	
				//ESP in sleep
			_delay_ms(10000);
		}
}
