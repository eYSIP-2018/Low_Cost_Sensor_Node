#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10);
const uint64_t pipes[3] = {0xF0F0F0F0E1LL,0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL};
void setup(void) {
Serial.begin(9600);
radio.begin();
radio.setDataRate(RF24_250KBPS);
radio.openReadingPipe(1, pipes[1]);// open pipe 1 for receipetion of data
radio.openReadingPipe(2, pipes[2]);// open pipe 2 for receipetion of data 
radio.startListening();//  make it as a Receiever
}
void loop(void)
{
unsigned char pipenum = 0;// variable to store which pipe 
char data[32] = "";
//char data2[32] = "";
while (radio.available(&pipenum))
{
  radio.read(&data, sizeof(data));// read data available on pipe and seperates payload
  Serial.print("data");
  Serial.println(pipenum);// pipe  number diffrentiate data is from which pipe
  Serial.println(data); 
}
//if ( radio.available() )
//{
//delay(500);
//radio.read(&data1, sizeof(data1));
//delay(500);
//radio.read(&data2, sizeof(data2));
//Serial.print("data1:");
////Serial.println(data1);
//Serial.print("data2:");
////Serial.println(data2);
//}
//else
//{
//Serial.println("No radio available");
//}
//delay(1000);
}

