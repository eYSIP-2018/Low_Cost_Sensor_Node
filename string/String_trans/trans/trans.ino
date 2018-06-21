#include <RF24_config.h>
#include <RF24.h>
#include <printf.h>
#include <nRF24L01.h>
#include <string.h>
#include <SPI.h>

int adr = 2; //node_id
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
  
  int data = analogRead(A0); //analogRead(100);
  int data1 = analogRead(A3);
  //int data2 = analogRead(A2);
  char data_arr[100] = ""; // initialising data for string
  char sen1[20]; //initialising buffer for itoa
  char sen2[20];
  //char sen3[20];
  char adrbuf[20]; //address buffer of node 
  
  itoa(data, sen1, 10); //itoa is used for converting int to string
  itoa(data1, sen2, 10);
  //itoa(data2, sen3, 10);
  itoa(adr, adrbuf, 10);
  strcat(data_arr, adrbuf);// strcat is for combining strings
  strcat(data_arr, "|");
  strcat(data_arr, sen1);
  strcat(data_arr, "|");
  strcat(data_arr, sen2);
  strcat(data_arr, "|");
 // strcat(data_arr, sen3);
  //strcat(data_arr, "|");
  
//  String senstr1 = String(data1);
//  String senstr = String(data);
//  String packet = String('<') + String('|') + String(data) + String('|') + String(data1)+ String('|') + String('>');
  
  radio.write(&data_arr, 100*sizeof(char)); //transmitting data_arr
  Serial.println(data_arr);
  
  
//  Serial.println(packet.length());
 delay(100);
//  Serial.println(packet);
}
