#include <RF24_config.h>
#include <RF24.h>
#include <printf.h>
#include <nRF24L01.h>
#include <string.h>
#include <SPI.h>

byte data[4] = "";

RF24 radio(9, 10);
const uint64_t pipes[6] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL };
void setup(void)
{
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipes[1]);
  radio.stopListening();
  
}
void loop(void)
{ 
  getdata();
  radio.write(data, sizeof(data)); //transmitting data_arr
  Serial.println(data[0]);
    
delay(100);
}

void getdata(void)
{
  data[0] = 1;
  data[1] = 250;
  data[2] = 200;
  data[3] = 100;
}

