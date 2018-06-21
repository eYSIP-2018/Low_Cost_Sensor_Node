#include <RF24_config.h>
#include <RF24.h>
#include <printf.h>
#include <nRF24L01.h>

#include <SPI.h>
int adr = 1;
int number[4] = {0,0,0,0};
int sen1;
int sen2;

char packet[100] = "";

//int i;
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
    
    
   while (radio.available())
   {
    //while (packet != '<')
    radio.read(&packet, 100*sizeof(char));
    
    parsePacket();
    
    Serial.print("Sensor1: ");
    Serial.println(sen1);
    Serial.print("Sensor2: ");
    Serial.println(sen2);
    
//    while (packet != '>')
//    {
//    radio.read(&packet, sizeof(packet));
    //Serial.println(packet);    
 } 
 
   delay(200);
 }

void resetNumber()
{
    number[0] = 0;
    number[1] = 0;
    number[2] = 0;
    number[3] = 0;
}


void parsePacket(){

    int i = 0;
    int j = 0;

    while(packet[i] != '\0'){
    
    
            for(j=0; j<3; j++){
                while(packet[i] != '|'){
                    number[j] = number[j]*10 + (packet[i] - '0');
                    i++;
                }
                if(j==0&&number[0]!= adr)
                return;
                i++;
            }
            sen1 = number[1];
            sen2 = number[2];
            resetNumber();
        }
}
