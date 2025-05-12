#include <WiFi.h>
#include <HTTPClient.h>
#include <painlessMesh.h>

#define   MESH_PREFIX     "yourMeshNetwork"
#define   MESH_PASSWORD   "meshPassword"
#define   MESH_PORT       5555

Scheduler     userScheduler;
painlessMesh  mesh;

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";
const char* serverUrl = "http://yourserver.com/insert.php";

void sendToMySQL(uint32_t fromNode, const String& msg) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String postData = "node=" + String(fromNode) + "&data=" + msg;

    int httpResponseCode = http.POST(postData);
    Serial.printf("[HTTP] code: %d\n", httpResponseCode);
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}

void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("Received from %u: %s\n", from, msg.c_str());
  sendToMySQL(from, msg);
}

void connectWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
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
