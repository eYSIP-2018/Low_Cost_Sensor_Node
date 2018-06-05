#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10);
const uint64_t pipes[3] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL };
void setup(void) 
{
Serial.begin(9600);
radio.begin();
radio.setDataRate(RF24_250KBPS);
radio.openWritingPipe(pipes[2]);// open pipe 2 for transmission with his own address
radio.stopListening();// makeTransmitter 
}

void loop(void)
{
const char text[] = "Hello2";
radio.write(&text, sizeof(text));// transmitt data
delay(50000);
}
