#include <RF24_config.h>
#include <RF24.h>
#include <printf.h>
#include <nRF24L01.h>
#include <string.h>
#include <SPI.h>

byte data[4] ={0,0,0,0};
byte data1[3] = ""; 

RF24 radio(9, 10);//starting an radio object
const uint64_t pipes[6] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL }; 
void setup(void)
{
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, pipes[1]);
  radio.openWritingPipe(pipes[0]);
  radio.startListening();
  
}
void loop(void)
{  
  if (radio.available())
   {
    radio.read(data, sizeof(data));
    Serial.println(data[3]);
    radio.closeReadingPipe(1);
    delay(100);

    radio.stopListening();
   
    delay(100); 

    getdata();
    Serial.println(data1[2]);
    radio.write(&data, sizeof(data)); //send data_arr array through radio
    radio.write(data1, sizeof(data1));
    
    
     delay(100);
     radio.openReadingPipe(1, pipes[1]);
     radio.startListening();
}
}

void getdata(void)
{
  data1[0] = 1;
  data1[1] = 250;
  data1[2] = 200;
  data1[3] = 25;
}
