#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <DHT.h>  // Including library for dht


 
String apiKey = "KPUGL5CQGX0XDESV";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "RedmiNote5pro";     // name of ur wifi
const char *pass =  "123456789"; // password of wifi
const char* server = "api.thingspeak.com"; // name of the server to which data is to be logged

#define DHTPIN 2          //pin where the dht22 is connected
 
DHT dht(DHTPIN, DHT22);

WiFiClient client;
 
void setup() 
{
       Serial.begin(115200);
       delay(10);
       dht.begin();
 
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
 
void loop() 
{
  
      float h = dht.readHumidity(); // this function is used to get humidity from d sensor
      float t = dht.readTemperature(); // this function is used to get temperature from d sensor
      
         
   if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
{  
      
       String postStr = apiKey;
       postStr +="&field1=";
       postStr += String(t);
       postStr +="&field2=";
       postStr += String(h);
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

       Serial.print("Temperature: ");
       Serial.print(t);
       Serial.print(" degrees Celcius, Humidity: ");
       Serial.print(h);
       Serial.println("%. Send to Thingspeak.");
  }
          client.stop();
 
          Serial.println("Waiting...");
  

  delay(10000);
}
