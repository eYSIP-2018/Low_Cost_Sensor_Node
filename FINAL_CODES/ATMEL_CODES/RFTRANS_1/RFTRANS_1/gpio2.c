/*
 * gpio2.c
 *
 * Created: 11-06-2018 17:04:20
 *  Author: sachin mahadevjadhav
 */ 
#include "gpio2.h"
volatile unsigned int cnt=0;//for timer counter delays and millis

/* To set a particular pin as input (IN)
 *  or output (OUT) .
 *  e.g Set_pin(13,OUT);
 */
//void Set_pin(unsigned char , unsigned char);
/* To set a particular output pin as a high or low by giving pin number and value.
 *  e.g. Write_Digital(13,high);
 */
//void Write_Digital (unsigned char , unsigned char );
//void UART_Init(uint32_t ); // initilzation of uart
///////////////////////////
void UART_Init()
{
  UCSR0B = 0x00;
  UCSR0A = 0x00; 
  UCSR0C|= (1<<UCSZ1) | (1<<UCSZ0)|(1<< USBS0);   // Asynchronous mode 8-bit data and 1-stop bit 
 // UBRR0L = 103;// 16MHZ for 9600 bps
  UBRR0L = 51; // 8MHZ Crystal set baud rate 9600(51) ,4800(103),2400(206) for serial transmission with external crystal oscilator at 8.0 MHz 
  UBRR0H = 0;
  UCSR0B |= (1<<RXEN) | (1<<TXEN);                  // Enable Receiver and Transmitter
}
//////////////
void UART_Transmit(unsigned char data )
{
 UCSR0A = 1<<TXC0;
/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) );
/* Put data into buffer, sends the data */
UDR0 = data;
while (!(UCSR0A & (1<<TXC0)));
}
/////////////////
////// to availble one byte
char UART_Available()
{
	return  ((UCSR0A & (1<<UDRE0)));
}
////// to read one byte
char UART_Read()
{
	while (!(UCSR0A & (1<<RXC0))); /* Wait until data exists. */
	//loop_until_bit_is_set(UCSR0A, RXC0);
	return UDR0;
}
/////////////////
void UART_Printfln(const char *text)
{
  unsigned char i=0;
  while (!(*(text+i) == '\0'))
  {
    UART_Transmit(*(text+i));
    i++;
  } 
  UART_Transmit('\n');
}
//////////

void UART_Printf(const char *text)
{
  unsigned char i=0;
  while (!(*(text+i) =='\0'))
  {
    UART_Transmit(*(text+i));
    i++;
  } 
}
/// to print  unsigned int number
void UART_Print_Num(unsigned int n)
{ 
	unsigned char ch=0;
	ch= n/10000+0x30;
	if(!(ch==0x30))
		UART_Transmit(ch);
	n=n%10000;
	ch=n/1000+0x30;
	if(!(ch==0x30))
		UART_Transmit(ch);
	n=n%1000;
	ch=n/100+0x30;
	if(!(ch==0x30))
		 UART_Transmit(ch);
	n=n%100;
	ch=n/10+0x30;
	if(!(ch==0x30))
		UART_Transmit(ch);
	ch=(n%10)+0x30;
    UART_Transmit(ch);	
    UART_Transmit('\n');	
}
///////////
/// to print unsigned char number
void UART_Print_Numchar(unsigned char n)
{
	unsigned char ch=0;
	ch=n/100+0x30;
	UART_Transmit(ch);
	n=n%100;
	ch=n/10+0x30;
	UART_Transmit(ch);
	ch=(n%10)+0x30;
	UART_Transmit(ch);
	UART_Transmit('\n');
}
///////////
void Set_pin (unsigned int num, unsigned int dir )
{
	if (dir == OUT )
	{  if (num >=8 )
		DDRB |= (1<<(num-8));
		else
		DDRD |= (1<<num);
	}
	else
	{
		if (num >=8 )
		DDRB |= (0<<(num-8));
		else
		DDRD |= (0<<num);
	}
}
/////////////
void Write_Digital (unsigned int num, bool value)
{
   cli();
    if (value  == high )
   {  
    if (num >= 8 )
           PORTB |= (1<<(num-8));
    else 
          PORTD |= (1<<num);
   }
   else 
    { 
      if (num >=8 )
           PORTB &= ~(1<<(num-8));
      else 
          PORTD &= ~(1<<num);
    }
   sei();
}
////timer0 in CTC mode with interrupt 
void timer0_init ()
{
	//set timer0 interrupt at 1kHz
	TCCR0A = 0;
	TCCR0B = 0;
	TCNT0  = 0;
	// set compare match register for 1khz increments
	OCR0A = 124;// = (8*10^6) / (1000*64) - 1 (must be <256)
	 // turn on CTC mode
	 TCCR0A |= (1 << WGM01);
	 // Set CS01 and CS00 bits for 64 prescaler
	 TCCR0B |= (1 << CS01) | (1 << CS00);
	 // enable timer compare interrupt
	 TIMSK0 |= (1 << OCIE0A);
}
// ISR for timer 0
ISR(TIMER0_COMPA_vect)
{
	cnt++;
};
//
// returns millis count value
unsigned int millis()
{
	//timer0_init();
	return cnt;
}
//////////////////////////////////////////////////////////////////////////
/////////Initilastion of ADC/////
void adc_init()
{
	DDRC = 0x00;//portc output
	PORTC = 0x00;//floating 
	ADCSRA = 0x83;// adc enable 125KHz adc clock(64 prescaler) , 
	ADMUX = 0x40;// selects ADC refrence as AVCC with external capacitor connected at VREF pin
}
///////////// ADC READ AND CONVERSION for given channel number ////
unsigned int adc_read(unsigned char num)
{
	unsigned int a;
	num = num & 0x07;
	ADMUX |= num;
	ADCSRA = ADCSRA | 0x40;   //Set start conversion bit
	while((ADCSRA&0x10)==0);  //Wait for ADC conversion to complete
	a = ADCL;
	a |= (ADCH<<8);//higher 2 bit
	ADCSRA = ADCSRA|0x10; //clear ADIF (ADC Interrupt Flag) by writing 1 to it
	return a;
}
// API function for setting u-controller in sleep mode for given time in minute
void power_down (unsigned int s_time)
{
	//for(int i=0;i<20;i++)
	//{
		//Set_pin(i,OUT);
		//
	//}
	//setup watchdog timer for 8s
	// comment below line if delay required in seconds
	// s_time = s_time*8;//as 1 for loop 8 sec sleep factor for 1 minute sleep
	WDTCSR = (24);//change WDCE and WDE also resets
	// WDTCSR = (33);//set prescalar for 8 sec timeout
	WDTCSR = 0x06; // set prescaler for 1 second timeout
	WDTCSR |=(1<<6);//enable interrupt mode WDIE set
	//Disable ADC
	ADCSRA &= ~(1<<7);//clear ADEN bit dont forget to set this bit while using ADC in main code
	 DIDR0=0x3F;//disable digital input buffers
	 DIDR1=0x03;//Disabled  AIN Digital Input Disable it reduces power consumption in digital input buffers
	// select sleep mode using SMCR.SM[2:0]
	SMCR |=(1<<2);//power down mode   010
	SMCR |=1;//enable sleep SMCR.SE set
	for (int i=0;i<s_time;i++)//gives extended timeout for 8*s_time sec
	{
		//BODS Disable
		// disable Brounout detection (BOD)
		MCUCR|=(3<<5);
		MCUCR = (MCUCR &~(1<<5)) | (1<<6);
		__asm__ __volatile__("sleep");// executes A sleep instruction
	}
}
////   ISR For WATCHDOG TIMER
ISR(WDT_vect)
{
	
};
///////////////////////
/// function to collect data from sensor user can add data depending on number of sensors

unsigned int adcinit(int channel)
{
	unsigned int result=0;
	float moisture=0;
	ADMUX = ADMUX & 0x00;// AND masking to selct a particular channel
	ADMUX = _BV(REFS0); // Select ADC refrence voltage as AVCC
	ADMUX = ADMUX | channel; // Selects ADC input channel number on which signal is connected
	_delay_ms(2); // Wait for Vref to settle
	ADCSRA |= _BV(ADSC) + _BV(ADEN); // Convert
	while (bit_is_set(ADCSRA,ADSC)); // wait till conversion Complete
	result = ADCL;// Read ADC result lower bytes
	result |= ADCH<<8;// Read ADC result higher bytes
	return result; // return unsigned int 16 bit ADC Conversion value	
}
uint8_t get_batt_voltage()
{
	unsigned int result=0;
	float res = 3.3/1024;
	float voltage;
	for(int i=0; i<5;i++)
	{
		result = result + adcinit(5);
	}
	//UART_Print_Num(result);
	//Serial.println(result);
	// To get actual battery voltage value  i.e. from 0 to 4.2 max
	voltage =  ((result/5)*res)/0.781;//calculation logic of external voltage divider network
	voltage = voltage * 10;// 4.2 *10 =42 to send single byte
	//UART_Print_Num((unsigned int)voltage);
	//Serial.println(voltage);
	return (uint8_t)abs(voltage);	
}
uint8_t get_temp( int ch)
{
	unsigned int result=0;
	float res = 3.3/1024;
	float temp;
	for(int i=0; i<5;i++)
	{
		result = adcinit(ch);
	}
	UART_Print_Num(result);	//Serial.println(result);
	temp = 186 - 0.3905*result;
	//voltage = voltage * 10;
	UART_Print_Num((unsigned int)temp);
	//Serial.println(voltage);
	return (uint8_t)abs(temp);
}
uint8_t get_soil_moisture()
{
	unsigned int result=0;
	float moisture;
	for(int i=0; i<5;i++)
	{
		result = result + adcinit(0);
	}
	UART_Print_Num(result);
	moisture = - 0.128 * (result/5) + 122; //curvefit
	//Serial.println(moisture); //moisture percentage
	return (uint8_t)abs(moisture);
}
//// function to collect all sensors data
void getdata()
{
	data[0] = get_batt_voltage();//battery voltage
	//data[1] = 75;
	data[1] =  get_soil_moisture();
	//data[1] = get_temp();//temp value from temp sensor
	data[2] = 29;//humidity value from DHTsensor
}
// turn on mosfet which is connected on D8 pin
void mosfet_on()
{
	DDRB |= 0x01;//mosfet D8 pin
	PORTB |= 0x00;// write 0 to D8 pin to turn ON P channel MOSFET
}
////////////////
// turn on mosfet which is connected on D8 pin
void mosfet_off()
{
	PORTB |= 0x01;// write 1 to D8 pin turn OFF P channel MOSFET
}
