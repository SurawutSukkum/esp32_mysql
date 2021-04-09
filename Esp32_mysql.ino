#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>



const char* ssid = "TESTESP";
const char* password = "a1234567";


String ID ="1235";
String postData;
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
}

void loop() {
    

    HTTPClient http;
    int temp = random(25,35);
    int humi = random(25,35);    
    String url = "http://192.168.43.172/esp32/esp32mysql/add.php?temp="+String(temp)+"&humi="+String(humi);
    Serial.println(url);
    http.begin(url); //HTTP
    
    int httpCode = http.GET();
      Serial.println(httpCode);
    if (httpCode > 0) {
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    Serial.println(payload);
    }
    } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
    
    delay(3000);
    
  }
  
