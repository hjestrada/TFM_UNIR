#include <SD.h>   //SD Card Bibliothek
#include <SPI.h>  //Bibliothek zum zugriff auf die SPI Schnittstelle des Arduinos

File outFile; // Die Datei welche geschrieben bzw. gelesen werden soll
int pinCS = 10; // Chip Select Pin 10 auf dem Arduino Uno
String filename = "temp.txt"; //Dateiname der zu lesenden bzw. schreibenden Datei

int val;   
int dat;  

int temperatursensorPin = 0 ;// Bestimmen das der Temperatursensor LM35 an den analogen PIN 0 angeschlossen ist.



void setup() {
  Serial.begin(9600); //Serielle Kommunikation mit 9600 Baud beginnen
  pinMode(pinCS, OUTPUT);
  if (SD.begin()){ //Wenn die SD Card initialisiert werden konnte dann....
    Serial.println("SD Karte konnte erfolgreich geladen werden!"); //Ausgabe des Textes auf der Seriellen Schnittstelle
  } else {
    //Dieser Block wird ausgeführt wenn die SD Card nicht initialisiert werden konnte.
    Serial.println("SD Karte konnte NICHT erfolgreich geladen werden!"); //Ausgabe des Textes auf der Seriellen Schnittstelle
    Serial.println("---Programm wird beendet!"); //Ausgabe des Textes auf der Seriellen Schnittstelle
    return; //vorzeitiges beenden der setup Methode
  }
}

void writeContent(int temp){
  outFile = SD.open(filename, FILE_WRITE); //Öffnet bzw. erzeugt die Datei im Modus schreibend
  if (outFile) { //Wenn die Datei existiert dann...
  
    outFile.print(",");
    outFile.print(temp);
    outFile.println("");
    outFile.close(); //Schließen der Datei (Dieses ist wichtig da sonst beim beenden des Sketches dies Daten verloren gehen können.)
  } else {
    //Dieser Block wird ausgeführt wenn die Datei nicht erzeugt werden konnte.
    Serial.println("Fehler beim öffnen der Datei test.txt"); //Ausgabe des Textes auf der Seriellen Schnittstelle
  }
}

int readTemperatur(){
  val = analogRead(temperatursensorPin); // Den analogen Wert des Temperatursensors lesen.
  dat = (125*val)>>8 ; // Aus dem gelesenen Wert die Temperatur berechnen.
  return dat;  // Temperatur zurück gegeben
}

void loop() {
  int temperatur = readTemperatur();
  writeContent(temperatur);
  delay(2000);
}
