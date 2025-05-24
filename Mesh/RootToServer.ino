#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "TESTESP";
const char* password = "0884118773";
const char* serverUrl = "http://ongri.com/TestESP/insert.php";

String msgMain=" ";

String generateRandomString(int length) {
  String chars = "0123456789";
  String randomStr = "";
  for (int i = 0; i < length; i++) {
   randomStr += chars[random(0, chars.length())];
  }
  return randomStr;
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
  Wifi_Connect();
  delay(3000);


}

void loop() {
    if (Serial1.available()>0) { 
       String msg = Serial1.readStringUntil('\r\n');
       msg.trim();
       Serial.println("Server Broadcasting: " + msg);
       //String msg = "node=7&Temp=127&Humi=127&Pressure=127&Led='ON'";
      sendToServer(msg);
      delay(1000);
    } 
}
 
