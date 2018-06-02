/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
unsigned cnt=0;
unsigned char p=0;
void setup()
{
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
}

void loop()
{
  
  radio.powerUp();
  const char text[] = "Hello";
  radio.write(&text, sizeof(text));
  delay(2000);
 radio.powerDown();
 delay(20000);
  cnt++;
  p=radio.getPALevel();
  Serial.print("Power Level:");
  Serial.println(p);
  Serial.print("Packet Count:");
  Serial.println(cnt);
  
}

