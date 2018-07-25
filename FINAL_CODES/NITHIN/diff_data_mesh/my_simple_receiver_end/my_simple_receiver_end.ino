

#include <RF24_config.h>
#include <RF24.h>
#include <printf.h>
#include <nRF24L01.h>

#include <SPI.h>

int i=1;
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
    char transdata[32] = "";
    unsigned char pipenum=0;
    char data[32] = "";  
    
   while (radio.available(&pipenum))
   {
   //Serial.println(pipenum);
    
    delay(100);
    i++;
    if(i%2==0)
    {
      radio.read(&transdata, sizeof(transdata));
      Serial.println(transdata);
     // Serial.println("transdata_received");
    
      Serial.println("transmitter1 data recieved ");
      Serial.println();
    }
    else
    {
      radio.read(&data, sizeof(data));
      Serial.println(data);
      Serial.print("transmitter2 from  data recieved");
      Serial.println();
      //Serial.println("datareceived:");
   }
    //Serial.print("i ");
    //Serial.println(i);
//   delay(1000);
 } 
 
   delay(200);
 
}

