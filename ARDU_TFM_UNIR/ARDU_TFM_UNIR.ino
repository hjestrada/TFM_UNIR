#include <SHT1x.h>
#include <PubSubClient.h>
#include <WiFiNINA.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "avr/dtostrf.h"
#include <SD.h>

File myFile;
int pinCS = 10;  // Pin 10 Arduino Nano 33 IoT

#define dataPin 3
#define clockPin 2
SHT1x sht1x(dataPin, clockPin);

#define dataPin2 8
#define clockPin2 4
SHT1x sht2x(dataPin2, clockPin2);

int led = 7;
int LedInterno = 13;
int Salida1 = 6;
int Salida2 = 9;
float temp;

void setup_wifi();
void reconnect();


#define TOKEN ""
#define DEVICEID "SAVACOFFEE"

const char* ssid = "Familia Murillo";      //Ingresar SSID de la red wifi
char* password = "17156673"; //Ingresar SSID de la red wifi
char mqtt_server[] = "broker.hivemq.com";//Ingresar broker mqtt.
//e122e9d8165c4e058ab2f6dba07b4aa2.s1.eu.hivemq.cloud
char publishTopic1[] = "qo41v3uchl/Zona1/Temperatura";
char publishTopic2[] = "qo41v3uchl/Zona1/Humedad";
char publishTopic3[] = "qo41v3uchl/Zona2/Temperatura";
char publishTopic4[] = "qo41v3uchl/Zona2/Humedad";
const char* topicAct = "qo41v3uchl/Actuador/";


String dataAct = "";

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);


void setup_wifi() {
  Serial.println();
  Serial.print("Conectando a: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    digitalWrite(led, LOW);
  }

  randomSeed(micros());
  Serial.println("");
  Serial.println("Conectado a la Red WIFI");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
}


void reconnect() {

  while (!mqtt.connected()) {

    if (mqtt.connect(DEVICEID, TOKEN, NULL)) {

      Serial.println("Conectado a  Broker MQTT");
      digitalWrite(LedInterno, HIGH);
    }

    else {
      Serial.print("Falló la Conexión, reconectando=");
      Serial.print(mqtt.state());
      Serial.println("Intentandolo de nuevo en 5 seg.");
      digitalWrite(LedInterno, LOW);
      //delay(1);
    }
  }
}

void setup() {



  pinMode(led, OUTPUT);
  pinMode(Salida1, OUTPUT);
  pinMode(Salida2, OUTPUT);
  pinMode(pinCS, OUTPUT);
  pinMode(LedInterno, OUTPUT);

  Serial.begin(9600);
  setup_wifi();
  mqtt.setServer(mqtt_server, 1883); //1883
  mqtt.setCallback(callback);

  // Inicialización SD
  if (SD.begin()) {
    Serial.println("SD card esta Lista para usar");
  } else {
    Serial.println("Falló al Inicializar SD card");
    return;
  }
  //---------------------------------------------
  myFile = SD.open("wifi.txt");//abrimos  el archivo
  if (myFile) {
    Serial.println("wifi.txt:");
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close(); //cerramos el archivo
  } else {
    Serial.println("Error al abrir el archivo");
  }
  //---------------------------------------------

}

void loop() {
  ConfigApp();
  Actuadores();
  if (!mqtt.connected()) {
    reconnect();
  }
  mqtt.loop();
  mqtt.subscribe(topicAct);
  float temp_c;
  float humidity;
  float temp_c2;
  float humidity2;
  temp_c = sht1x.readTemperatureC();
  humidity = sht1x.readHumidity();
  temp_c2 = sht2x.readTemperatureC();
  humidity2 = sht2x.readHumidity();

  //-------------------------------
  char buffer1[10];
  dtostrf(temp_c, 0, 2, buffer1);
  mqtt.publish(publishTopic1, buffer1);
  //-------------------------------
  char buffer2[10];
  dtostrf(humidity, 0, 2, buffer2);
  mqtt.publish(publishTopic2, buffer2);
  //-------------------------------

  char buffer3[10];
  dtostrf(temp_c2, 0, 2, buffer3);
  mqtt.publish(publishTopic3, buffer3);
  //-------------------------------
  char buffer4[10];
  dtostrf(humidity2, 0, 2, buffer4);
  mqtt.publish(publishTopic4, buffer4);
  //-------------------------------
}

void ConfigApp() {

  if (Serial.available() > 0) {
    String CadenaRecibida = Serial.readStringUntil('\n');
    Serial.print("Recibido: ");
    Serial.println(CadenaRecibida);
    ssid = CadenaRecibida.c_str();
    Serial.flush();
  }
}

void Actuadores() {

  if (dataAct == "AC1/ON") {
    digitalWrite(led, HIGH);
  }
  if (dataAct == "AC1/OFF") {
    digitalWrite(led, LOW);
  }

  //-------------------------
  if (dataAct == "AC2/ON") {
    digitalWrite(led, HIGH);
  }
  if (dataAct == "AC2/OFF") {
    digitalWrite(led, LOW);
  }

  Serial.println(dataAct);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje Recibido[");
  Serial.print(topic);
  Serial.print("] ");
  char dataArray[length];
  int i = 0;
  for (i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    dataArray[i] = (char)payload[i];
  }
  Serial.println();
  dataAct = String(dataArray);
}
