#include <printf.h>
#include <string.h>
void setup(void)
{
  Serial.begin(9600);
  pinMode (3,OUTPUT);
 // pinMode (13,OUTPUT); 
}
void loop(void)
{   
  byte sen1[]={25,75,34,99};
  char z;
  unsigned char i=0;
  //wake up esp32  after coming all data  of nodes 
  digitalWrite(3,HIGH);
    delay(100);
  digitalWrite(3,LOW);
//   for (i=0;i<3;i++)
//   {
//     Serial.write(sen1[i]);
//          //delay(1000);
//   }  
//  delay(100);
 //    Serial.print(sen1);
   //wait for ACK
 while (Serial.available())
 {
   // Serial.println("A");
   z = Serial.read();
  // Serial.print(z);
   if (z =='C')
   {
            //send packet
            unsigned char i=0;
//            delay(1000); 
           for (i=0;i<4;i++)
           {
             Serial.write(sen1[i]);
//           //delay(1000);
           }  
   }
   //ESP in sleep
    delay(1000);
  }

}


