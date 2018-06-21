

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

String apiKey = "KPUGL5CQGX0XDESV";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "Redmi";     // replace with your wifi ssid and wpa2 key
const char *pass =  "123456789";
const char* server = "api.thingspeak.com";

WiFiClient client;

//String inputString = "";         // a String to hold incoming data
//boolean stringComplete = false;  // whether the string is complete
//String val;
float val;
HardwareSerial Serial2(2);

void setup()
{
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1,16,17);
//  inputString.reverse(200);  

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


void loop() {
  // Read serial input:
    Serial2.available();
    float val = Serial2.parseFloat();

    //Serial.println(val);
  
    

   if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += val;
//                             postStr +="&field2=";
//                             postStr += String(h);
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
                             Serial.println(postStr);
                             

                           }
          client.stop();
 
          Serial.println("Waiting...");
          
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(10000);
}







