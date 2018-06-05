#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);
const uint64_t pipes[3] = {0xF0F0F0F0E1LL,0xF0F0F0F0E2LL,0xF0F0F0F0E3LL };// pipe addresses
void setup(void) {
Serial.begin(9600);
radio.begin();
radio.setDataRate(RF24_250KBPS);// set data rate 250 kbps
radio.openWritingPipe(pipes[1]);// open pipe 1 with his own address
radio.stopListening();// mae it transmitter
}
void loop(void)
{
const char text[] = "Hello1";
radio.write(&text, sizeof(text));// send data packet
delay(10000);
Serial.println("data1 sent");
}

