#include <printf.h>
#include <string.h>
void setup(void)
{
  Serial.begin(9600);
  pinMode (3,OUTPUT);// pin connected to interrupt pin of ESP32
}
void loop(void)
{   
  byte sen1[]={25,75,34,99};//dummy data to send form sensors
  char z;
  unsigned char i=0;
  //wake up esp32  after coming  data of all nodes 
  digitalWrite(3,HIGH);
  delay(100);
  digitalWrite(3,LOW);

   //wait for ACK
 while (Serial.available())
 {
   z = Serial.read();
   if (z =='C')
   {
            //send packet
           for (i=0;i<4;i++)
           {
             Serial.write(sen1[i]);
           }  
   }
   //ESP in sleep after sending data
    delay(1000);
  }

}


