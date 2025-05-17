#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>

#include <painlessMesh.h>

#define MESH_PREFIX     "espMesh"
#define MESH_PASSWORD   "mesh1234"
#define MESH_PORT       5555

Scheduler     userScheduler;
painlessMesh  mesh;

const char* ssid = "TESTESP";
const char* password = "0884118773";
const char* serverUrl = "http://ongri.com/TestESP/insert.php";

String msgMain=" ";


void connectWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}


void WGET(String msgGet)
{
      HTTPClient http;
    String randomData = generateRandomString(3); // 10-character random string
    String postData = msgGet;//"node="+randomData+"&Temp="+ randomData + "&Humi="+ randomData + "&Pressure="+ randomData + "&Led="+ randomData;
    String url = "https://ongri.com/TestESP/insert1.php?"+postData;
    Serial.println(url);
    http.begin(url); //HTTP
    
    int httpCode = http.GET();
    Serial.println(httpCode);
    if (httpCode > 0) {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);    
        delay(500);
      } 
    } 
    http.end();
}

String generateRandomString(int length) {
  String chars = "0123456789";
  String randomStr = "";
  for (int i = 0; i < length; i++) {
   randomStr += chars[random(0, chars.length())];
  }
  return randomStr;
}




void sendToServer(String postData) {
  Wifi_Connect();
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://ongri.com/TestESP/insert1.php?" + postData;
    Serial.println("Sending to: " + url);

    http.begin(url);
    int httpCode = http.GET();

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

void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("Received from %u: %s\n", from, msg.c_str());

  // Example: assume msg is already in query string format
  // e.g., "node=2&Temp=294&Humi=294&Pressure=294&Led=ON"
  

 
  sendToServer(msg);
}

void Wifi_Connect()
{
    // Connect to Wi-Fi
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  delay(2000);
  WiFi.begin(ssid, password);

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
void setup() {
  Serial.begin(115200);
  Wifi_Connect();
  delay(3000);

  // Start mesh
  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
  mesh.onReceive(receivedCallback);

}

void loop() {
  mesh.update();
}
