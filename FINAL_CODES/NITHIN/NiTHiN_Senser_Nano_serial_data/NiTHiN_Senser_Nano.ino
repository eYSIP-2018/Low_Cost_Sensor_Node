//#include <RF24_config.h>
//#include <RF24.h>
#include <printf.h>
//#include <nRF24L01.h>
#include <string.h>
#include <SPI.h>
#include <DHT.h>
#include <HardwareSerial.h>
int adr = 1; //node address
int number[4] = {0,0,0,0};
int tsen1;
int tsen2;
//char trans_packet[100] = "";
const int interrupt_pin = 3;
DHT dht(2, DHT22); // sensor data pin 2, type of sensor used

//const uint64_t pipes[6] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL }; 

void setup(void)
{
  pinMode(interrupt_pin, OUTPUT);
  
//  HardwareSerial Serial();
  Serial.begin(9600);
  
  dht.begin();
  
}
void loop(void)
{ 
  digitalWrite(interrupt_pin, HIGH);
  delay(500);
  digitalWrite(interrupt_pin, LOW);
  delay(500);

  if (Serial.available()>0)
  {
     Serial.read();
  float data  = dht.readHumidity(); //(h)reads digital data at pin 2
  float data1 = dht.readTemperature(); //(t)
  //int data2 = analogRead(A2);
  //char data_arr[100] = ""; // data array for packet
  char sen1[20]; 
  char sen2[20];
  String senData = "";
  //char sen3[20];
  //char adrbuf[20];
   
//  itoa(adr, adrbuf, 10); // itoa() function converts integer to string
  dtostrf(data, 2, 2, sen1); //dtostrf() function converts float to string
  dtostrf(data1, 2, 2, sen2);
//  itoa(data2, sen3, 10);
  
  //strcat(data_arr, adrbuf); //strcat() function concatenate two strings
//  strcat(data_arr, "<");
  //  strcat(data_arr, sen1);
//  strcat(data_arr, "|");
//  strcat(data_arr, sen2);
//  strcat(data_arr, ">");
  //strcat(data_arr, sen3);
  //strcat(data_arr, "|");
  //strcat(data_arr, trans_packet);
  
  
  //Serial.println(data_arr);
//  Serial.print("H:");
//  Serial.print(data);
//  Serial.print("% ");
//  Serial.print("T:");
//  Serial.print(data1);
//  Serial.println("*C");
      senData = senData + sen1;
      senData = senData + "   ";
      senData = senData + sen2;
//      senData = sen1 + "    " + sen2;
   Serial.print(senData);
   delay(1000);
     //senData = "";

}
}


