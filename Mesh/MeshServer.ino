#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>

#include <painlessMesh.h>

#define MESH_PREFIX     "espMesh"
#define MESH_PASSWORD   "mesh1234"
#define MESH_PORT       5555

Scheduler     userScheduler;
painlessMesh  mesh;

#define RXD1 (25) 
#define TXD1 (26) 

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
//Sending to: https://ongri.com/TestESP/insert1.php?node=2&Temp=170&Humi=170&Pressure=170&Led='OFF'
//Server response: save OK2
//
void sendToServer(String postData) {

    String url = postData;
    Serial.println("Sending to: " + url);
    Serial1.println("Sending to: " + url);
    
}

void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("Received from %u: %s\n", from, msg.c_str());

  // Example: assume msg is already in query string format
  // e.g., "node=2&Temp=294&Humi=294&Pressure=294&Led=ON"
  sendToServer(msg);
}

void sendMessage() {
  while (Serial1.available()) { 
  String msg = Serial1.readString();
  mesh.sendBroadcast(msg);
  Serial.println("Server Broadcasting: " + msg);
    }

}

Task taskSendMessage(TASK_SECOND * 1, TASK_FOREVER, &sendMessage);
void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, RXD1, TXD1); 
  // Start mesh
  mesh.setDebugMsgTypes(ERROR | STARTUP | CONNECTION);
  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
  mesh.onReceive(&receivedCallback);

  userScheduler.addTask(taskSendMessage);
  taskSendMessage.enable();
}

void loop() {
  mesh.update();
}
