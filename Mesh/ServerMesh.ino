#include <painlessMesh.h>
#include <WiFi.h>
#include <HTTPClient.h>  // Only on the server node

#define   MESH_PREFIX     "yourMeshNetwork"
#define   MESH_PASSWORD   "meshPassword"
#define   MESH_PORT       5555

Scheduler     userScheduler;
painlessMesh  mesh;

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";
const char* serverUrl = "http://yourapi.com/data";

void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("Received from %u: %s\n", from, msg.c_str());
  sendToAPI(msg);  // Send to cloud
}

void sendToAPI(const String& payload) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST("{\"data\":\"" + payload + "\"}");

    Serial.printf("HTTP Response code: %d\n", httpResponseCode);
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}

void connectWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void setup() {
  Serial.begin(115200);
  connectWiFi();

  mesh.setDebugMsgTypes(ERROR | STARTUP | CONNECTION);
  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
  mesh.onReceive(&receivedCallback);
}

void loop() {
  mesh.update();
}
