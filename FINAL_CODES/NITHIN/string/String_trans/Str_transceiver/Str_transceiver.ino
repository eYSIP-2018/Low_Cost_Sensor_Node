#include <RF24_config.h>
#include <RF24.h>
#include <printf.h>
#include <nRF24L01.h>
#include <string.h>
#include <SPI.h>
#include <DHT.h>

int adr = 1; //node address
int number[4] = {0,0,0,0};
int tsen1;
int tsen2;
char trans_packet[100] = "";

DHT dht(14, DHT22); // sensor data pin 2, type of sensor used
RF24 radio(9, 10);//starting an radio object

const uint64_t pipes[6] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL }; 

void setup(void)
{
  Serial.begin(9600);
  dht.begin();
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
    radio.read(&trans_packet, 100*sizeof(char));
    
    parsePacket();
//    Serial.print("tsensor1: ");
//    Serial.println(tsen1);
//    Serial.print("tsensor2: ");
//    Serial.println(tsen2);
    radio.closeReadingPipe(1);
    delay(100);

    radio.stopListening();
   
   
   
  delay(100); 
  
  float data  = dht.readHumidity(); //(h)reads digital data at pin 2
  float data1 = dht.readTemperature(); //(t)
  int data2 = analogRead(A2);
  char data_arr[100] = ""; // data array for packet
  char sen1[20]; 
  char sen2[20];
  char sen3[20];
  char adrbuf[20];
   
  itoa(adr, adrbuf, 10); // itoa() function converts integer to string
  dtostrf(data, 2, 2, sen1); //dtostrf() function converts float to string
  dtostrf(data1, 2, 2, sen2);
  itoa(data2, sen3, 10);
  
  strcat(data_arr, adrbuf); //strcat() function concatenate two strings
  strcat(data_arr, "|");
  strcat(data_arr, sen1);
  strcat(data_arr, "|");
  strcat(data_arr, sen2);
  strcat(data_arr, "|");
  strcat(data_arr, sen3);
  strcat(data_arr, "|");
  strcat(data_arr, trans_packet);
  
//  String senstr1 = String(data1);
//  String senstr = String(data);
//  String packet = String('<') + String('|') + String(data) + String('|') + String(data1)+ String('|') + String('>');
  
  bool ok = radio.write(&data_arr, 100*sizeof(char)); //send data_arr array through radio
  if(ok)
  {
    Serial.println("true");
  }
  else
  {
    Serial.println("failed");
  }
  Serial.println(data_arr);
  Serial.print("H:");
  Serial.print(data);
  Serial.print("% ");
  Serial.print("T:");
  Serial.print(data1);
  Serial.println("*C");
   delay(100);
   radio.openReadingPipe(1, pipes[1]);
   radio.startListening();
}
}
void parsePacket(){

    int i = 0;
    int j = 0;

    while(trans_packet[i] != '\0'){
    
    
            for(j=0; j<3; j++){
                while(trans_packet[i] != '|'){
                    number[j] = number[j]*10 + (trans_packet[i] - '0');
                    i++;
                }
                if(j==0&&number[0]!= adr)
                return;
                i++;
            }
            tsen1 = number[1];
            tsen2 = number[2];
            resetNumber();
        }
}


void resetNumber()
{
    number[0] = 0;
    number[1] = 0;
    number[2] = 0;
    number[3] = 0;
}

