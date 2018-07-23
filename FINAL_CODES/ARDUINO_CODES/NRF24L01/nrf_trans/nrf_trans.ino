// Incude necessary header files for NRF24L01+
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN connected to pin of pro mini
const byte address[6] = "00001";// address of transmitter 
unsigned cnt=0;//variable for packet count
unsigned char p=0;// variabe to get power level value 

/*  NRF24L01: -18dBm, -12dBm,-6dBM, and 0dBm 
 *            MIN   , LOW , HIGH  , MAX
 * /
  */
///////////////////////////////////////
// Funvtion to initialize the module
void setup()
{
  // uncommnet this To turn on Mosfet on WSN board
//  pinMode(8,OUTPUT);
//  digitalWrite(8,LOW);
//  delay(10);
  Serial.begin(9600);
  radio.begin();// begi the radio with default conditions
  // data_rate = 1MBps, PA_Level = MAX
  radio.openWritingPipe(address);//open  pipe for transmission 
  radio.setPALevel(RF24_PA_MIN);// SET PA level LOW (-18 dBm)
  radio.setDataRate(RF24_250KBPS);//set data rate 250 kbps, other options are (1MBps,2MBps)
  radio.stopListening();// make radio transmitter ready to tarnsmitt.
 
}
//////////////////////////////////////
// The function runs continuously
void loop()
{
  const char text[] = "Hello";//data string to be sent
  radio.write(&text, sizeof(text));// write data to TXFIFO of nrf24l01 
  //transmitt data  Active transmission
  delay(2000);// wait for transmission 
   //after TXFIFO empty it goes in standby mode (datasheet current 26uA observed 40uA)
  radio.powerDown();//nrf24l01 goes in powerdown mode (datasheet current consumption 900nA practically DMM is showing zero)
  delay(20000);// wait in power down mode to take reading on DSO
  cnt++;// increase count of packet 
  p=radio.getPALevel();// get Power amplifier level
  Serial.print("Power Level:");
  Serial.println(p);
  Serial.print("Packet Count:");
  Serial.println(cnt); 
}

