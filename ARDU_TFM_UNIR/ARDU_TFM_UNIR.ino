#include <SHT1x.h>
#include <PubSubClient.h>
#include <WiFiNINA.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include "avr/dtostrf.h"

#define dataPin 3
#define clockPin 2
SHT1x sht1x(dataPin, clockPin);

#define dataPin2  8
#define clockPin2 4
SHT1x sht2x(dataPin2, clockPin2);

int led = 7;
int Salida1 = 6;
int Salida2 = 9;
float temp;

void setup_wifi();
void reconnect();


#define TOKEN  ""
#define DEVICEID "SAVA"

const char* ssid = "NODO 1_TECNOPARQUE";
const char* password = "Tecnoparque789*";
const char mqtt_server[] = "broker.hivemq.com";
const char publishTopic[] = "qo41v3uchl/Zona2/Temperatura";
static char payload[256];

StaticJsonDocument<256> doc;

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);


void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Conectando a: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
    digitalWrite(led, LOW);
  }

  randomSeed(micros());
  Serial.println("");
  Serial.println("Conectado a la Red WIFI");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
  digitalWrite(led, HIGH);
}
void reconnect() {

  while (!mqtt.connected()) {

    if (mqtt.connect(DEVICEID, TOKEN, NULL)) {

      Serial.println("Conectado a  Broker MQTT");
      // digitalWrite(led, HIGH);
    }

    else
    {
      Serial.print("Falló la Conexión, reconectando=");
      Serial.print(mqtt.state());
      Serial.println("Intentandolo de nuevo en 5 seg.");
      //digitalWrite(led, LOW);
      delay(5000);

    }

  }

}

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(Salida1, OUTPUT);
  pinMode(Salida2, OUTPUT);
  Serial.begin(9600);
  setup_wifi();
  mqtt.setServer(mqtt_server, 1883);

}

void loop()
{
  if (!mqtt.connected())
  {
    reconnect();
  }

  mqtt.loop();

  float temp_c;
  float humidity;
  float temp_c2;
  float humidity2;
  temp_c = sht1x.readTemperatureC();
  humidity = sht1x.readHumidity();
  temp_c2 = sht2x.readTemperatureC();
  humidity2 = sht2x.readHumidity();

  doc["Temperatura Zona 1"] = temp_c;
  doc["Humedad Zona 1"] = humidity;
  doc["Temperatura Zona 2"] = temp_c2;
  doc["Humedad Zona 2"] = humidity2;



//  serializeJsonPretty(doc, payload);
//  mqtt.publish(publishTopic, payload);

  char buffer[10];
  dtostrf(temp_c, 0, 2, buffer);
  mqtt.publish(publishTopic, buffer);


  Serial.println(buffer);
  delay(5000);
}
