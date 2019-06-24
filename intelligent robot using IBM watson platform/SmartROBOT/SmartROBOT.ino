#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "MLRITM-PLACEMENT";
const char* password = "Mlritm@123";

#define ORG "y1y4sn"
#define DEVICE_TYPE "pranavi"
#define DEVICE_ID "pranavi123"
#define TOKEN "pranavi1"
String command;
char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/cmd/home/fmt/String";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;
//Serial.println(clientID);

WiFiClient wifiClient;
void callback(char* topic, byte* payload, unsigned int payloadLength);
PubSubClient client(server, 1883, callback, wifiClient);
void setup() {
  Serial.begin(115200);
  Serial.println();
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  wifiConnect();
  mqttConnect();
}

void loop() {
  if (!client.loop()) {
    mqttConnect();
  }
delay(100);
}

void wifiConnect() {
  Serial.print("Connecting to "); Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("nWiFi connected, IP address: "); Serial.println(WiFi.localIP());
}

void mqttConnect() {
  if (!client.connected()) {
    Serial.print("Reconnecting MQTT client to "); Serial.println(server);
    while (!client.connect(clientId, authMethod, token)) {
      Serial.print(".");
      delay(500);
    }
    initManagedDevice();
    Serial.println();
  }
}
void initManagedDevice() {
  if (client.subscribe(topic)) {
    Serial.println("subscribe to cmd OK");
  } else {
    Serial.println("subscribe to cmd FAILED");
  }
}

void callback(char* topic, byte* payload, unsigned int payloadLength) {
  Serial.print("callback invoked for topic: "); Serial.println(topic);

  for (int i = 0; i < payloadLength; i++) {
    //Serial.println((char)payload[i]);
    command += (char)payload[i];
  }
Serial.println(command);
if(command == "MOVE FORWARD"){
  //digitalWrite(D1,LOW);
  Serial.println("Moving FORWARD");
   digitalWrite(D1,LOW);
  digitalWrite(D2,HIGH);
  digitalWrite(D3,HIGH);
  digitalWrite(D4,LOW);
}
else if(command == "MOVE BACKWARD"){
  //digitalWrite(D1,HIGH);
  Serial.println("Moving BACKWARD");
    digitalWrite(D1,HIGH);
  digitalWrite(D2,LOW);
  digitalWrite(D3,LOW);
  digitalWrite(D4,HIGH);
}
else if(command == "MOVE RIGHT"){
  //digitalWrite(D1,HIGH);
  Serial.println("moving right");
   digitalWrite(D1,HIGH);
  digitalWrite(D2,LOW);
  digitalWrite(D3,HIGH);
  digitalWrite(D4,LOW);
}
else if(command == "MOVE LEFT"){
  //digitalWrite(D1,HIGH);
  Serial.println("moving left");
   digitalWrite(D1,LOW);
  digitalWrite(D2,HIGH);
  digitalWrite(D3,LOW);
  digitalWrite(D4,HIGH);
  
}
else if(command == "STOP"){
  //digitalWrite(D1,HIGH);
  Serial.println("stop");
  digitalWrite(D1,LOW);
  digitalWrite(D2,LOW);
  digitalWrite(D3,LOW);
  digitalWrite(D4,LOW);

}
command ="";
}
