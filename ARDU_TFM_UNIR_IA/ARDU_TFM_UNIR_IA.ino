#include <SD.h>
#include <WiFiNINA.h>
#include <SHT1x.h>
#include <PubSubClient.h>
#include "avr/dtostrf.h"


#define ledRojo 7
#define TOKEN ""
#define DEVICEID "SAVACOFFEE"

//Define los pines del sensor temp y Hum SHT10
#define dataPin 3
#define clockPin 2
SHT1x sht1x(dataPin, clockPin);

#define dataPin2 8
#define clockPin2 4
SHT1x sht2x(dataPin2, clockPin2);

//Define las variables para lectura de valores de los sensores SHT10

float temp_c;
float humidity;
float temp_c2;
float humidity2;


const int SD_CS_PIN = 10;  // Pin de selección de tarjeta SD

const char* ssid = "tostador";
const char* password = "milu1234";
char mqtt_server[] = "broker.hivemq.com";  //Ingresar broker mqtt.
int puertoMQTT = 1883;                     //Ingresar puerto mqtt.


char publishTopic1[] = "qo41v3uchl/Zona1/Temperatura";
char publishTopic2[] = "qo41v3uchl/Zona1/Humedad";
char publishTopic3[] = "qo41v3uchl/Zona2/Temperatura";
char publishTopic4[] = "qo41v3uchl/Zona2/Humedad";
const char* topicAct = "qo41v3uchl/Actuador/";

String dataAct = "";
WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);


void reconnectBroker() {

  while (!mqtt.connected()) {

    if (mqtt.connect(DEVICEID, TOKEN, NULL)) {

      Serial.println("Conectado a  Broker MQTT");

    }

    else {
      Serial.print("Falló la Conexión al Broker, reconectando=");
      Serial.println(mqtt.state());
      Serial.println("Intentandolo de nuevo en 5 seg.");
      ;
    }
  }
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

void Actuadores() {

  if (dataAct == "AC1/ON") {
    Serial.println("Salida 1 activada");
  }
  if (dataAct == "AC1/OFF") {
    Serial.println("Salida 1 apagada");
  }

  //-------------------------
  if (dataAct == "AC2/ON") {
    Serial.println("Salida 2 activada");
  }
  if (dataAct == "AC2/OFF") {
    Serial.println("Salida 2 apagada");
  }

  Serial.println(dataAct);
}



void setup() {

  // Led Rojo Tarjeta
  pinMode(ledRojo, OUTPUT);
  // Led verde Arduino
  pinMode(LED_BUILTIN, OUTPUT);

  // Inicializar serial
  Serial.begin(9600);

  // Inicializar broker MQTT
  mqtt.setServer(mqtt_server, puertoMQTT);  //1883
  mqtt.setCallback(callback);

  // Inicializar SD
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("Error al inicializar SD");
    return;
  }

  // Abrir archivo que contiene SSID y contraseña
  File file = SD.open("wifi.txt");
  if (!file) {
    Serial.println("Error al abrir archivo wifi.txt");
    return;
  }

  // Leer parametros de Configuración Inicial.

  String ssid_temp = file.readStringUntil('\n');
  String password_temp = file.readStringUntil('\n');

  file.close();

  //ssid = ssid_temp.c_str();
  // password = password_temp.c_str();

  // Conectarse a WiFi
  WiFi.begin(ssid, password);
  WiFi.setHostname("SAVA_BASIC");

  while (WiFi.status() != WL_CONNECTED) {
    delay(10000);
    Serial.println("Intentando conectar a WiFi...");
    digitalWrite(ledRojo, LOW);
  }

  Serial.println("Conectado a WiFi");
  Serial.println("Dirección IP:");
  Serial.println(WiFi.localIP());
  digitalWrite(ledRojo, HIGH);
}

void loop() {

  Actuadores();

  if (!mqtt.connected()) {
    reconnectBroker();
  }
  mqtt.loop();
  mqtt.subscribe(topicAct);


  temp_c = sht1x.readTemperatureC();
  humidity = sht1x.readHumidity();
  temp_c2 = sht2x.readTemperatureC();
  humidity2 = sht2x.readHumidity();

  //----------Publicando Tópicos---------------------
  char buffer1[10];
  dtostrf(temp_c, 0, 2, buffer1);
  mqtt.publish(publishTopic1, buffer1);
  //-------------------------------------------------
  char buffer2[10];
  dtostrf(humidity, 0, 2, buffer2);
  mqtt.publish(publishTopic2, buffer2);
  //-------------------------------------------------

  char buffer3[10];
  dtostrf(temp_c2, 0, 2, buffer3);
  mqtt.publish(publishTopic3, buffer3);
  //-------------------------------------------------
  char buffer4[10];
  dtostrf(humidity2, 0, 2, buffer4);
  mqtt.publish(publishTopic4, buffer4);
  //-------------------------------------------------
  Serial.println("Tópicos publicados Exitosamente");
}
