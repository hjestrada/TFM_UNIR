#include <SPI.h>
#include <SD.h>
#include <WiFi.h>

const int chipSelect = 4;
String ssid, password;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  if (!SD.begin(chipSelect)) {
    Serial.println("No se pudo inicializar la SD");
    return;
  }

  File configFile = SD.open("config.txt");
  if (!configFile) {
    Serial.println("No se pudo abrir el archivo de configuración");
    return;
  }

  while (configFile.available()) {
    String line = configFile.readStringUntil('\n');
    int splitIndex = line.indexOf(":");
    String key = line.substring(0, splitIndex);
    String value = line.substring(splitIndex + 1);
    if (key == "SSID") {
      ssid = value;
    } else if (key == "PASSWORD") {
      password = value;
    }
  }

  configFile.close();

  WiFi.begin(ssid.c_str(), password.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Conectando a WiFi...");
    delay(1000);
  }
  Serial.println("Conectado a WiFi");
}

void loop() {
  // Agrega aquí el código adicional que deseas ejecutar
  // una vez conectado a la red Wi-Fi
}
