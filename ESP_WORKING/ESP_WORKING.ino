#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
//#define bat 0
#define tmp 0
#define hmd 1

String apiKey = "L22QTULTOGQ1RUQN";     //  Enter your Write API key from ThingSpeak
String apiKey_1 = "8R6HHDXRVDFO1FDH";
const char *ssid =  "Nithin_RedmiNote5pro";     // replace with your wifi ssid and wpa2 key
const char *pass =  "123456789";
const char* server = "api.thingspeak.com";

WiFiClient client;

String sen1;
byte data[7]="";


HardwareSerial Serial2(2);

void setup()
{
  Serial.begin(115200);
  Serial2.begin(2400,SERIAL_8N1,16,17);// 16 RX 17 Tx
  Serial.println("Connecting to ");
       Serial.println(ssid);
       WiFi.begin(ssid, pass);
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
 //esp_sleep_enable_ext0_wakeup(GPIO_NUM_33,1); //1 = High, 0 = Low
      Serial.println("");
      Serial.println("WiFi connected");
       
}


void loop() 
{
//  byte tmp1,tmp2,tmp3,tmp4;
//  byte hmd1,hmd2,hmd3,hmd4;
//   byte z=0;
//   byte i=0;
//    
//     Serial2.write('C'); 
//     
//     delay(4000);
//    while(Serial2.available()&&((z!=1)|(z!=2)|(z!=3)|(z!=4)))
//      {
//       
//         z = Serial2.read();
//       if (z!=' ')
//        {
//          data[i] = z;
//          i++; 
//         }
//       Serial.println(z);
//     }
//     if (z==1)
//      { tmp1 = data[tmp];
//        hmd1 = data[hmd];
//        }
//        if (z==2)
//      { tmp2 = data[tmp];
//        hmd2 = data[hmd];
//      }
//         if (z==3)
//      { tmp3 = data[tmp];
//        hmd3 = data[hmd];
//       }
//         if (z==4)
//      { tmp4 = data[tmp];
//        hmd4 = data[hmd];
//       }
      
      if (client.connect(server,80))  
      {    
         for(int i=1; i<2; i++);
        {  
         String postStr = apiKey;
         postStr +="&field1=";
         postStr +=25;
         postStr +="&field2=";
         postStr +=70;
//         postStr +="&field3=";
//         postStr +=tmp2;
//         postStr +="&field4=";
//         postStr +=hmd2;
         postStr += "\r\n\r\n";

         client.print("POST /update HTTP/1.1\n");
         client.print("Host: api.thingspeak.com\n");
         client.print("Connection: close\n");
         client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
         client.print("Content-Type: application/x-www-form-urlencoded\n");
         client.print("Content-Length: ");
         client.print(postStr.length());
         client.print("\n\n");
         client.print(postStr);
        }
      }
      client.stop();
        
        if (client.connect(server,80))
        {  
        for(int i=2; i<=2; i++)
        {
         String postStr_1 = apiKey_1;
         postStr_1 +="&field1=";
         postStr_1 +=30;
         postStr_1 +="&field2=";
         postStr_1 +=50;
//         postStr_1 +="&field3=";
//         postStr_1 +=tmp4;
//         postStr_1 +="&field4=";
//         postStr_1 +=hmd4;
         postStr_1 += "\r\n\r\n";
        
         client.print("POST /update HTTP/1.1\n");
         client.print("Host: api.thingspeak.com\n");
         client.print("Connection: close\n");
         client.print("X-THINGSPEAKAPIKEY: "+apiKey_1+"\n");
         client.print("Content-Type: application/x-www-form-urlencoded\n");
         client.print("Content-Length: ");
         client.print(postStr_1.length());
         client.print("\n\n");
         client.print(postStr_1); 
        } 
      }
      client.stop();
      delay(15000);
      //if(z==4) // data received form all nodes
       // esp_deep_sleep_start();
     
 // Serial2.write(z);
//    delay(100);
//    while(Serial2.available())
//    {
//    esp_deep_sleep_start();
//    Serial.print("insleep");
//    }
 
}
