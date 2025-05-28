#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;
const char* ssid = "TESTESP";
const char* password = "0884118773";
const char* serverUrl = "http://ongri.com/TestESP/insert.php";

String msgMain=" ";
//User Setting
String nodeID = "8";
String LED_Status = "OFF";
int pinLed = 23;
String generateRandomString(int length) {
  String chars = "0123456789";
  String randomStr = "";
  for (int i = 0; i < length; i++) {
   randomStr += chars[random(0, chars.length())];
  }
  return randomStr;
}
void sendToServerLED(int Node) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://ongri.com/TestESP/ReadLEDStatus.php?node=" + String(Node);
    Serial.println("Sending LED to: " + url);

    http.begin(url);
    int httpCode = http.GET();
    Serial.println("httpCode LED: " + httpCode);

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Server response LED Status: " + payload);
      if(payload.indexOf("Led=ON")>0)
      {
       LED_Status = "ON";
       digitalWrite(pinLed,HIGH);
       Serial.println("LEDState===========>: "+LED_Status);
      }
      if(payload.indexOf("Led=OFF")>0)
      {
       LED_Status = "OFF";
       digitalWrite(pinLed,LOW);
       Serial.println("LEDState===========>: "+LED_Status);
      }
    } else {
      Serial.println("HTTP GET failed, error: " + http.errorToString(httpCode));
    }

    http.end();
  } else {
    Serial.println("Wi-Fi not connected");
    Wifi_Connect();
  }
}
void sendToServer(String postData) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://ongri.com/TestESP/insert1.php?" + postData;
    Serial.println("Sending to: " + url);

    http.begin(url);
    int httpCode = http.GET();
    Serial.println("httpCode: " + httpCode);

    if (httpCode > 0) {
      String payload = http.getString();

      Serial.println("Server response: " + payload);
    } else {
      Serial.println("HTTP GET failed, error: " + http.errorToString(httpCode));
    }

    http.end();
  } else {
    Serial.println("Wi-Fi not connected");
    Wifi_Connect();
  }
}

void sendMessage() {
  
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");



  String led = LED_Status;
  String quotedLed = "'" + led + "'";
  String randomData = generateRandomString(3); // 10-character random string
  String msg =  "node=9&Temp=" + String(bme.readTemperature()) + "&Humi="+ String(bme.readHumidity()) + "&Pressure="+ String(bme.readPressure() / 100.0F) + "&Led="+quotedLed ;
  
  Serial.println("Broadcasting: " + msg);
  sendToServer(msg);
}
 

void Wifi_Connect()
{
    // Connect to Wi-Fi
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  delay(2000);
  WiFi.begin(ssid, password);
  delay(2000);
  Serial.print("Connecting to Wi-Fi");

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 20) {
    delay(500);
    Serial.print(".");
    retries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected!");
    Serial.println(WiFi.localIP());
  } else {
   Serial.println("\nFailed to connect.");
    Serial.print("Status: ");
    Serial.println(WiFi.status());
  }
  /*6 = WL_DISCONNECTED
  3 = WL_CONNECTED
  1 = WL_NO_SSID_AVAIL
  4 = WL_CONNECT_FAILED*/
}
#define RXD1 (25) 
#define TXD1 (26) 
void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, RXD1, TXD1); 
  pinMode(pinLed,OUTPUT);
  Wifi_Connect();
  delay(3000);
  bme.begin(0x76);

}

void loop() {
         sendToServerLED(9);
         sendMessage();
         delay(3000);       
}
 
