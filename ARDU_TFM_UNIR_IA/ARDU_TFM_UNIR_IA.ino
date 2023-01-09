#include <SD.h>
#include <WiFiNINA.h>

const int SD_CS_PIN = 10; // Pin de selección de tarjeta SD

void setup() {
  // Inicializar serial
  Serial.begin(9600);

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

  // Leer SSID y contraseña del archivo
  String ssid = file.readStringUntil('\n');
  String password = file.readStringUntil('\n');
  String broker = file.readStringUntil('\n');
  int port = file.readStringUntil('\n').toInt();
  file.close();

  // Conectarse a WiFi
  WiFi.begin(ssid.c_str(), password.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }

  Serial.println("Conectado a WiFi");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Tu código aquí
}
