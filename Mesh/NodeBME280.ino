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

//User Setting
String nodeID = "8";
String LED_Status = "OFF";
int pinLed = 12;


void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("Received from %u: %s\n", from, msg.c_str());

  String dataReceived = msg.c_str();
  String data = "node="+nodeID+"&Led=";
  int LEDReadNo = dataReceived.indexOf(data);
  Serial.println("LEDReadNo===========>: "+String(LEDReadNo));

  if(LEDReadNo == 0)
  {
      Serial.println("dataReceived===========>: "+String(dataReceived));
      Serial.println("LEDReadNo===========>: "+String(LEDReadNo));
      //Received from 996935125: node=8&Led=d<br>
      //dataReceived===========>: node=8&Led=d<br>
      //dataReceived===========>: node=8&Led=OFF<br>
      //LEDReadNo===========>: 0
      //LEDState===========>: d
      //
      //
      if(dataReceived.indexOf("Led=ON")>0)
      {
       LED_Status = "ON";
       digitalWrite(pinLed,HIGH);
       Serial.println("LEDState===========>: "+LED_Status);
      }
      if(dataReceived.indexOf("Led=OFF")>0)
      {
       LED_Status = "OFF";
       digitalWrite(pinLed,LOW);
       Serial.println("LEDState===========>: "+LED_Status);
      }
  }
 
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



  String led = LED_Status;
  String quotedLed = "'" + led + "'";
  String randomData = generateRandomString(3); // 10-character random string
  //String msg =  "node=7&Temp=" + String(bme.readTemperature()) + "&Humi="+ String(bme.readHumidity()) + "&Pressure="+ String(bme.readPressure() / 100.0F) + "&Led="+quotedLed ;
  String msg =  "node="+String(nodeID)+"&Temp=" + String(randomData) + "&Humi="+ String(randomData) + "&Pressure="+ String(String(randomData)) + "&Led="+quotedLed ;

  mesh.sendBroadcast(msg);
  Serial.println("Broadcasting: " + msg);
}

Task taskSendMessage(TASK_SECOND * 1, TASK_FOREVER, &sendMessage);

void setup() {
  Serial.begin(115200);

  pinMode(ledPin,OUTPUT);
  //bme.begin(0x76);


  mesh.setDebugMsgTypes(ERROR | STARTUP | CONNECTION);
  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
  mesh.onReceive(&receivedCallback);

  userScheduler.addTask(taskSendMessage);
  taskSendMessage.enable();
}

void loop() {
  
  mesh.update();
}
