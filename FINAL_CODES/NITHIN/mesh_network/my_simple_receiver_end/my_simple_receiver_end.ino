

#include <RF24_config.h>
#include <RF24.h>
#include <printf.h>
#include <nRF24L01.h>

#include <SPI.h>

RF24 radio(9, 10);
const uint64_t pipes[6] = {0xF0F0F0F0E1LL,0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL};

void setup(void)
 {
   
   Serial.begin(9600);
   radio.begin();
   radio.setDataRate(RF24_250KBPS);
   radio.openReadingPipe(0, pipes[0]);
   radio.startListening(); // node will work as a simple_receiver node
     
 }
void loop(void)
 {
    unsigned char pipenum=0;
    char data[32] = "";  
   while (radio.available(&pipenum))
   {
     
    radio.read(&data, sizeof(data));
    Serial.println(data);
    Serial.println(pipenum);
    Serial.println("datareceived:");
   
 } 
   delay(200);
 
}

