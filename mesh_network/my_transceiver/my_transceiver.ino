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
   radio.openReadingPipe(1, pipes[1]);
   radio.openWritingPipe(pipes[0]);
   radio.startListening(); // node will work as a Main_receiver node
   
  
 }
void loop(void)
 {
   char data[32] = "";
   if (radio.available())
   {
    radio.read(&data, sizeof(data));
    
    Serial.println(data);
    Serial.println("data received");
    radio.closeReadingPipe(1);
    delay(100);
    radio.stopListening(); 
    
    
    radio.setRetries(5,15);
    if(radio.write(&data, sizeof(data)));
    
      Serial.println(data);
      Serial.println("data sent");
    
    delay(100);
    radio.openReadingPipe(1, pipes[1]);
    radio.startListening();
    }  
 }
 
