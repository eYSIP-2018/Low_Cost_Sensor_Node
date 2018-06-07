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
#define USBS0  3
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
  UCSR0A = 0x00; 
  UCSR0C|= (1<<UCSZ1) | (1<<UCSZ0)|(1<< USBS0);   // Asynchronous mode 8-bit data and 1-stop bit                                 // Clear the UASRT status register
  UBRR0L |= 51; // set baud rate 9600 for serial transmission with external crystal oscilator at 8.0 MHz 
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

void UART_Printfln(unsigned char *text)
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
void UART_Printf( unsigned char *text)
{
  unsigned char i=0;
  while (!(*(text+i) =='\0'))
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
   {  
    if (num >= 8 )
           PORTB = (1<<(num-8));
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
// Main code

unsigned int cnt=0;
unsigned char flg =0;
int main()
{
  
 cli();
//set timer0 interrupt at 2kHz
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
  Set_pin(13, OUT); 
  UART_Init(9600);
  
  sei();
  
  while (1)
  {
    if ((cnt==100)&&(flg==0))
    {
     Write_Digital(13, high);
     cnt=0;
     flg=1;
    }  
    if ((cnt==100)&&(flg==1))
    {
     Write_Digital(13, low);
     cnt=0;
     flg=0;
    } 
    //UART_Printfln("SACHIN1234");
    //UART_Transmit('A');
    //UART_Transmit ('\n');
  }
}
ISR(TIMER0_COMPA_vect)
{
 cnt++;
}
