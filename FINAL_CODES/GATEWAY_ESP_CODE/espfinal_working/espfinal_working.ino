#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
// macros for data sequence in received packet
#define bat 0           // battery level is first byte
#define tmp 1           // first sensor data is second byte
//#define hmd 1
String apiKey = "L22QTULTOGQ1RUQN";     //  Enter your Write API key from ThingSpeak
const char *ssid =  "sj";     // replace with your wifi ssid and wpa2 key
const char *pass =  "sachinjadhav";
const char* server = "api.thingspeak.com";
WiFiClient client;
String sen1;
byte data[7]="";
// varaibles for storing received field data 
byte tmp1,tmp2,tmp3,tmp4;
byte hmd1,hmd2,hmd3,hmd4;
byte d1=0,d2=0,d3=0,d4=0;///flags for data check
void http_request();
HardwareSerial Serial2(2);

// setup code runs only once
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
      Serial.println("");
      Serial.println("WiFi connected");     
}

// the following code runs continuously
void loop() 
{
 
   byte z=0;//flag for checking received node data
   byte i=0;// loop counter variable
  //for handshaking with ESP32
   Serial2.write('C'); 
   //wait for data available on serial pin which is sent by arduino 
   delay(4000);
   // check data is available and data of all node is received by checking flags 
    while(Serial2.available()&&((z!=1)|(z!=2)|(z!=3)|(z!=4)))
      {
        //Serial.print("got data");
         z = Serial2.read();
       if (z!=' ')
        {
          data[i] = z;
          i++; 
         }
       Serial.println(z);
     }
     // update data variables  according to fields
     if (z==1)
      { tmp1 = data[tmp];
        hmd1 = data[hmd];
        d1=1;
       }
        if (z==2)
      { tmp2 = data[tmp];
        hmd2 = data[hmd];
        d2=1;
      }
         if (z==3)
      { tmp3 = data[tmp];
        hmd3 = data[hmd];
        d3=1;
       }
         if (z==4)
      { tmp4 = data[tmp];
        hmd4 = data[hmd];
        d4=1;
       }
      //Seril.println(sen1);
      // upload data on thingspeak server using ESP32
        http_request();
 
}
// post request to send data on Thingspeak (Internet)
void http_request()
{
     if (client.connect(server,80))  
      {
         String postStr = apiKey;// adding key of channel key in thingspeak
         postStr +="&field1=";// address of field1
         postStr +=tmp1;// value of filed1 which will be plotted on graph
         postStr +="&field2=";
         postStr +=hmd1;
         postStr +="&field3=";
         postStr +=tmp2;
         postStr +="&field4=";
         postStr +=hmd2;
         postStr +="&field5=";
         postStr +=tmp3;
         postStr +="&field6=";
         postStr +=hmd3;
         postStr +="&field7=";
         postStr +=tmp4;
         postStr +="&field8=";
         postStr +=hmd4;
         postStr += "\r\n\r\n";
           client.print("POST /update HTTP/1.1\n");
           client.print("Host: api.thingspeak.com\n");
           client.print("Connection: close\n");
           client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
           client.print("Content-Type: application/x-www-form-urlencoded\n");
           client.print("Content-Length: ");
           client.print(postStr.length());
           client.print("\n\n");
           client.print(postStr); //send this whole request to server with above specified format
      }
      client.stop();
      // wait for next data transmission
      delay(15000);
}



