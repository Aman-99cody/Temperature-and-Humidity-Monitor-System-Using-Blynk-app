#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"
#include <Blynk.h>
#define BLYNK_PRINT Serial

const char* ssid = "........";
const char* pass = "......";

char auth[] = "...........";
#define DHTPIN D1
DHT dht (DHTPIN ,DHT11);

BlynkTimer timer;

void sendSensor()
{
  float h=dht.readHumidity();
  float t=dht.readTemperature();
 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, t);
 //delay(100);
  Blynk.virtualWrite(V6, h);
  //Serial.println(t);
  if(t>25)
  {
    Blynk.notify("Temperature exceeds 25 degrees C");
    Serial.println(t);
    Serial.println("Temperature exceeds 25 degrees C");
  }
  if(h>=50)
  {
     Blynk.notify("Humidity exceeds 50%");
     Serial.println("Humidity exceeds 50%");
     Serial.println(h);
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
Blynk.begin(auth, ssid, pass);
timer.setInterval(1000L, sendSensor);
 
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Blynk.run();
  //delay(500);
  timer.run();
}
