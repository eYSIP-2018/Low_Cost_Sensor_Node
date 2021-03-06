#include <avr/interrupt.h>
#define LED_PIN 8
void setup()
{
 pinMode(LED_PIN,OUTPUT);
 digitalWrite(LED_PIN,HIGH);
 // make all pin output except led pin to reduce power consumption in sleep mode
  for(int i=0;i<20;i++)
  {
    //if (i !=13)
    pinMode(i,OUTPUT);
   // digitalWrite(i,LOW);
  }

   //setup watchdog timer for 8s 
  WDTCSR = 0x18;//(24);//change WDCE and WDE also resets 
  // Uncomment one of the line from following 2 lines depending on your requirement
  WDTCSR = (33);//set prescalar for required timeout 8 sec 
 //  WDTCSR = 0x06;// set prescer for 1 seconds
  WDTCSR |=(1<<6);//enable interrupt mode
 //Disable ADC
   ADCSRA &= ~(1<<7);//clear ADEN bit 
   DIDR0=0x3F;//disable digital input buffers
   DIDR1=0x03;//Disabled  AIN Digital Input Disable it reduces power consumption in digital input buffers
   // select sleep mode using SMCR .SM[2:0]
   SMCR |=(1<<2);//power down mode   010
   SMCR |=1;//enable sleep SMCR.SE set
}
// following function runs continuously
void loop()
{
  for (int i=0;i<2;i++)//gives extended timeout 16 sec
  { 
   //BODS Disable
   // disable Brounout detection (BOD)
   MCUCR|=(3<<5);
   MCUCR = (MCUCR &~(1<<5)) | (1<<6);
   __asm__ __volatile__("sleep");// to execute sleep instruction in C code
  }
}
// ISR for wdt
ISR(WDT_vect)
{
};
 
