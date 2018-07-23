// include necessary header files for NRf24L01+ module
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
unsigned char p=0,cnt=0;// variables for power level and packet count
const byte address[6] = "00001"; //5 Byte address of nrf device
/*  NRF24L01: -18dBm, -12dBm,-6dBM, and 0dBm 
 *            MIN   , LOW , HIGH  , MAX
 * /
  */
//////////////////////////////////////////////////
// initialsation function runs only once when uController is Reseted
void setup() 
{
    // uncommnet this To turn on Mosfet on WSN board
//  pinMode(8,OUTPUT);
//  digitalWrite(8,LOW);
//  delay(10);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0,address);//accept/check data availble on pipe number 0 with same address
 //radio.setPALevel(RF24_PA_MIN); // sets power Amplifier level
  radio.startListening();// Make Radio Receiver
  radio.setDataRate(RF24_250KBPS);// set minimum data rate 250Kbps
}
//////////////////////////////////////////////////////
// The loop function runs continuously 
void loop() 
{
  // uncomment following 3 lines to check signal strength
     // bool t;
    //t = radio.testRPD();
    //Serial.println(t ? "Strong signal > 64dBm" : "Weak signal < 64dBm" );
    // check for data is availble on channel
    if (radio.available()) 
    {
      char text[32] = "";
      radio.read(&text, sizeof(text));// Read data
      Serial.println(text);
      Serial.print("Packet count:");
      Serial.println(cnt);
      cnt++;
      p=radio.getPALevel();// Read power level
      Serial.print("Power Level:");
      Serial.println(p); 
   }//if end 
}// loop end 
