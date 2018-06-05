#define OUT 1
#define IN  0
#define LED 13
#define high 1
#define low  0
#define TXEN 3
#define RXEN 4
#define UCSZ0 1
#define UCSZ1 2
#define UDRE0 5
#define UCSRE0 6
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
void UART_Init(uint32_t v_baudRate_u32)
{
  UCSR0B = 0x00;
  UCSR0A= 0x00; 
  UCSR0C|= (1<<UCSZ1) | (1<<UCSZ0);   // Asynchronous mode 8-bit data and 1-stop bit                                 // Clear the UASRT status register
  UBRR0L = 51; // set baud rate 9600 for serial transmission with external crystal oscilator at 8.0 MHz 
  UBRR0H = 0;
  UCSR0B |= (1<<RXEN) | (1<<TXEN);                  // Enable Receiver and Transmitter
}
//////////////
void UART_Transmit( unsigned char data )
{
 // UCSR0A = 1<<TXC0;
/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) );
/* Put data into buffer, sends the data */
UDR0 = data;
//while (!(UCSR0A & (1<<TXC0)));
}
/////////////////

void UART_Printfln(unsigned char *text)
{
  unsigned char i=0;
  while (!(*text == '\0'))
  {
    UART_Transmit(*(text+i));
    i++;
  } 
  UART_Transmit('\n');
}
//////////
void UART_Printf(unsigned char *text)
{
  unsigned char i=0;
  while (!(*text=='\0'))
  {
    UART_Transmit(*(text+i));
    i++;
  } 
}
///////////
void Set_pin (unsigned char num, unsigned char dir )
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
void Write_Digital (unsigned char num, unsigned char value)
{
   cli();
    if (value  == high )
   {  if (num >=8 )
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
// the setup function runs once when you press reset or power the board

void setup()
{
  cli();
  // initialize digital pin 13 as an output.
  Set_pin(13, OUT); 
  UART_Init(9600);
  //Serial.begin(9600);
  sei();
}
// the loop function runs over and over again forever
void loop() 
{
  //Write_Digital(13, high);   // turn the LED on (HIGH is the voltage level)
  //delay(1000);              // wait for a second
  //Write_Digital(13, low);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
  UART_Printfln("SACHIN");
//  Serial.println("Sachin");
  delay(2000);
}
