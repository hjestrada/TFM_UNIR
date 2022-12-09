/*
  Pines de Arduino
** MOSI - pin 11
** MISO - pin 12
** CLK - pin 13
** CS - pin 10

  Pines LCD
  (7, 6, 5, 8, 3, 2)

  SALIDAS PINES  1 Y  0
  DHT PINES 9 Y 4

  RTC A4-A5

*/
#include <SD.h> // Se incluye la libreria SD.h
#include <Wire.h>
#include <SPI.h>
#include <LiquidCrystal.h>
#include "DHT.h"
#include "RTClib.h"
//#include "Timer.h"

#define DHTPIN 9
#define DHTTYPE DHT11
#define DHTPIN2 4

File Archivodatos; // Se crea un tipo de archivo llamado Archivodatos
RTC_DS1307 rtc;
Timer tiempo;
DHT dht1(DHTPIN, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 8, 3, 2);
//LiquidCrystal lcd(RS, Enable, D4, D5, D6, D7)

byte IconoGota[8] = {0x4, 0x4, 0xa, 0xa, 0x11, 0x11, 0x11, 0xe};
byte IconoTermo[8] = {0x4, 0xa, 0xa, 0xe, 0xe, 0x1f, 0x1f, 0xe};
byte IconoGrados[8] = {0x1c, 0xf4, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0};
int diaSD;
int mesSD;
int anioSD;
int horaSD;
int minuSD;
int segSD;
String dataString = "";
float promTemp;
float promHum;
boolean estado = false;


void setup() {
  
  // Se añaden los caracteres especiales al objeto LCD:
  lcd.createChar(0, IconoGota);
  lcd.createChar(1, IconoTermo);
  lcd.createChar(2, IconoGrados);

  int tickEvent = tiempo.every(300000, GuardarSD); // Llama a la funcion GuardarSD cada 1 hora(3600000)millis
  dht1.begin();
  dht2.begin();
  rtc.begin();
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(2, 0);
  lcd.print("  AGRO-IOT ");
  lcd.setCursor(1, 1);
  lcd.print("-S.A.V.A 4.0-");
  delay(3000);
  lcd.clear();

  //-----------------------------

  pinMode(10, OUTPUT); // se asigana el pin de control CS
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  lcd.setCursor(3, 0);
  lcd.print("Iniciando");
  lcd.setCursor(3, 1);
  lcd.print("SD card...");
  delay(1000);
  lcd.clear();

  if (! rtc.begin()) {
    lcd.setCursor(3, 0);
    lcd.println("Error    "); // Si no fue inicializada se notifica
    lcd.setCursor(3, 1);
    lcd.println("RTC!      ");
    while (1);
  }

  if (! rtc.isrunning()) {
    lcd.setCursor(3, 0);
    lcd.println("RTC no se "); // Si no fue inicializada se notifica
    lcd.setCursor(3, 1);
    lcd.println("ejecuta");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }


  if (!SD.begin(10)) { // se confirmar si la memoria esta inicializa
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.println("Inicio       "); // Si no fue inicializada se notifica
    lcd.setCursor(3, 1);
    lcd.println(" Fallido!     ");
    delay(1000);
    lcd.clear();
    return;
  }
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.println("Inicio     ");// si no hubo problemas se notifica
  lcd.setCursor(3, 1);
  lcd.println(" Exitoso!    ");
  delay(1000);
  lcd.clear();
}

void loop() {

  tiempo.update();

  DateTime now = rtc.now();
  diaSD = (now.day());
  mesSD = (now.month());
  anioSD = (now.year());
  horaSD = (now.hour());
  minuSD = (now.minute());
  segSD = (now.second());

  float h1 = dht1.readHumidity();
  float t1 = dht1.readTemperature();
  float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();

  promTemp = (t1 + t2) / 2;
  promHum = (h1 + h2) / 2;

  if ((isnan(t1) || isnan(h1)) || ( isnan(t2) || isnan(h2) )) {
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.println("Error      ");
    lcd.setCursor(4, 1);
    lcd.println("Sensores    ");
    delay(2000);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TEMP: ");
    lcd.print(promTemp);
    lcd.print(" ");
    lcd.write(byte(2));
    lcd.print("C ");
    lcd.write(byte(1));
    lcd.setCursor(0, 1);
    lcd.print("HMR: ");
    lcd.print(promHum);
    lcd.print("  %  ");
    lcd.write(byte(0));
    delay(2500);

    if ((promHum > 55) || (promTemp > 36)) {
      digitalWrite(1, HIGH);
      digitalWrite(0, HIGH);
      delay(1000);
      estado = true;

    }
    else {
      digitalWrite(1, LOW);
      digitalWrite(0, LOW);
      delay(1000);
      estado = false;


    }
  }


}


void GuardarSD() {

  Archivodatos = SD.open("datos.txt", FILE_WRITE); //Se Crea un archivo llamado datos con extensión CSV

  if (Archivodatos) {

    //--------Acople de trama Fecha------------
    dataString = String(diaSD);
    dataString += "/";
    dataString += String(mesSD);
    dataString += "/";
    dataString += String(anioSD);

    dataString += "/";
    dataString += String(horaSD);
    dataString += ":";
    dataString += String(minuSD);
    dataString += ":";
    dataString += String(segSD);

    Archivodatos.print(dataString);
    Archivodatos.print(";");
    Archivodatos.print(promTemp);
    Archivodatos.print(";");
    Archivodatos.print(promHum);
    Archivodatos.print(";");
    Archivodatos.println(estado);
    Archivodatos.close(); // se cierra el archivo
    Archivodatos.flush();
  }
  else {
    lcd.clear();
    lcd.setCursor(1, 0); lcd.print("Error al Abrir");
    lcd.setCursor(1, 1); lcd.print("el archivo");
    delay(2000);
    lcd.clear();
  }
}
