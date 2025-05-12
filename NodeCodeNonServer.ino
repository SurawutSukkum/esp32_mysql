#include <painlessMesh.h>
#include <WiFi.h>
#include <HTTPClient.h>  // Only on the server node

#define   MESH_PREFIX     "yourMeshNetwork"
#define   MESH_PASSWORD   "meshPassword"
#define   MESH_PORT       5555

Scheduler     userScheduler;
painlessMesh  mesh;

void sendMessage() {
  String msg = "Hello from node " + mesh.getNodeId();
  mesh.sendBroadcast(msg);
}

void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("Received from %u: %s\n", from, msg.c_str());
}

void setup() {
  Serial.begin(115200);
  mesh.setDebugMsgTypes(ERROR | STARTUP | CONNECTION);
  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
  mesh.onReceive(&receivedCallback);

  userScheduler.setInterval(10000, sendMessage);  // Send message every 10s
}

void loop() {
  mesh.update();
}
