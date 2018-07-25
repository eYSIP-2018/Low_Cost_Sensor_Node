//#include <RF24_config.h>
//#include <RF24.h>
#include <printf.h>
//#include <nRF24L01.h>
#include <string.h>
#include <SPI.h>
#include <DHT.h>

int adr = 1; //node address
int number[4] = {0,0,0,0};
int tsen1;
int tsen2;
//char trans_packet[100] = "";

DHT dht(2, DHT22); // sensor data pin 2, type of sensor used

const uint64_t pipes[6] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL }; 

void setup(void)
{
  Serial.begin(9600);
  dht.begin();
  
}
void loop(void)
{   
 // float data  = dht.readHumidity(); //(h)reads digital data at pin 2
  float data1 = dht.readTemperature(); //(t)
  //int data2 = analogRead(A2);
  char data_arr[100] = ""; // data array for packet
  char sen1[20]; 
  char sen2[20];
  //char sen3[20];
  //char adrbuf[20];
   
//  itoa(adr, adrbuf, 10); // itoa() function converts integer to string
  //dtostrf(data, 2, 2, sen1); //dtostrf() function converts float to string
  dtostrf(data1, 2, 2, sen2);
//  itoa(data2, sen3, 10);
  
  //strcat(data_arr, adrbuf); //strcat() function concatenate two strings
  //strcat(data_arr, "|");
  //strcat(data_arr, sen1);
  //strcat(data_arr, "|");
  strcat(data_arr, sen2);
  //strcat(data_arr, "|");
  //strcat(data_arr, sen3);
  //strcat(data_arr, "|");
  //strcat(data_arr, trans_packet);
  

  Serial.println(data_arr);
//  Serial.print("H:");
//  Serial.print(data);
//  Serial.print("% ");
  Serial.print("T:");
  Serial.print(data1);
  Serial.println("*C");
   Serial.write(data_arr);
   Serial.println();
   delay(1000);
}


