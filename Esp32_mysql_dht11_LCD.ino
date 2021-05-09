#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>

#include "DHT.h"
#include <LCD_I2C.h>
LCD_I2C lcd(0x27);

#define DHTPIN 2 
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "TESTESP";// เปลี่ยน ssid ก่อนทดลอง
const char* password = "a1234567";// เปลี่ยน password ก่อนทดลอง

void setup() {
  Serial.begin(115200);
  delay(500);
 
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  };
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  dht.begin();

  lcd.begin();
  lcd.backlight();
}

void loop() {
    
 

    
    HTTPClient http;
    
    int temp = dht.readTemperature();
    int humi = dht.readHumidity(); 
    
                  // เปลี่ยน ip ก่อนทดลอง    
    String url = "http://192.168.43.172/esp32/esp32mysql/add.php?temp="+String(temp)+"&humi="+String(humi);
                 // http://192.168.43.172/esp32/esp32mysql/add.php?temp=100&humi=123
    Serial.println(url);
    http.begin(url); //HTTP
    
    int httpCode = http.GET();
    Serial.println(httpCode);
    if (httpCode > 0) {
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    Serial.println(payload);    
    lcd.clear();
    lcd.print("[HTTP] code: "); 
    lcd.println(httpCode); 
    lcd.setCursor(0, 1); 
    lcd.print(payload);
    delay(500);
    }
    } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    lcd.clear();
    lcd.print("[HTTP] code: "); 
    lcd.println( httpCode); 
    lcd.setCursor(0, 1); 
    lcd.print("GET... failed");
    }
    http.end();
    
    delay(3000);
    
  }
  
