#include <painlessMesh.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;


#define MESH_PREFIX     "espMesh"
#define MESH_PASSWORD   "mesh1234"
#define MESH_PORT       5555

Scheduler userScheduler;
painlessMesh mesh;

void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("Received from %u: %s\n", from, msg.c_str());
}
String generateRandomString(int length) {
  String chars = "0123456789";
  String randomStr = "";
  for (int i = 0; i < length; i++) {
   randomStr += chars[random(0, chars.length())];
  }
  return randomStr;
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


  int state = random(0, 2);
  String led = (state == HIGH ? "ON" : "OFF") ;
  String quotedLed = "'" + led + "'";
  String randomData = generateRandomString(3); // 10-character random string
  String msg =  "node=1&Temp=" + String(bme.readTemperature()) + "&Humi="+ String(bme.readHumidity()) + "&Pressure="+ String(bme.readPressure() / 100.0F) + "&Led="+quotedLed ;
  mesh.sendBroadcast(msg);
  Serial.println("Broadcasting: " + msg);
}

Task taskSendMessage(TASK_SECOND * 1, TASK_FOREVER, &sendMessage);

void setup() {
  Serial.begin(115200);


  bme.begin(0x76);


  mesh.setDebugMsgTypes(ERROR | STARTUP | CONNECTION);
  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
  mesh.onReceive(&receivedCallback);

  userScheduler.addTask(taskSendMessage);
  taskSendMessage.enable();
}

void loop() {
  
  mesh.update();
}
