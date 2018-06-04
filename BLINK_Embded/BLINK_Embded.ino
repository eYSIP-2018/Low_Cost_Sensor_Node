// the setup function runs once when you press reset or power the board
#define OUT 1
#define IN  0
#define LED 13
#define high 1
#define low  0
/* To set a particular pin as input (IN)
 *  or output (OUT) .
 *  e.g Set_pin(13,OUT);
 */
void Set_pin(unsigned char , unsigned char);
/* To set a particular output pin as a high or low by giving pin number and value.
 *  e.g. Write_Digital(13,high);
 */
void Write_Digital (unsigned char , unsigned char );
void Set_pin (unsigned char num, unsigned char dir )
{ 
   if (dir == OUT )
   {  if (num >=8 )
           DDRB |= (1<<(num-8));
      else 
          DDRB |= (1<<num);
   }
   else 
    { 
      if (num >=8 )
           DDRB |= (0<<(num-8));
      else 
          DDRB |= (0<<num);
      }
}
void Write_Digital (unsigned char num, unsigned char value)
{
    if (value  == high )
   {  if (num >=8 )
           PORTB |= (1<<(num-8));
      else 
          PORTB |= (1<<num);
   }
   else 
    { 
      if (num >=8 )
           PORTB &= ~(1<<(num-8));
      else 
          PORTB &= ~(1<<num);
    }
}
void setup()
{
  // initialize digital pin 13 as an output.
  Set_pin(13, OUT); 
}
// the loop function runs over and over again forever
void loop() 
{
  Write_Digital(13, high);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  Write_Digital(13, low);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}
