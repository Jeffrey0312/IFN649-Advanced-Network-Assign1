#include "DHT.h"
//#include <SoftwareSerial.h>

#define DHTPIN 21      // Digital pin connected to the DHT sensor
//#define DHTPIN_photo 20
#define DHTTYPE DHT11   // DHT 11

//#define LEDPIN 13

DHT dht(DHTPIN, DHTTYPE);


// Teensy 5V <--> HC-05 Vcc
// Teensy Ground <--> HC-05 GND
#define rxPin 7 // Teensy pin 7 <--> HC-05 Tx
#define txPin 8 // Teensy pin 8 <--> HC-05 Rx
//SoftwareSerial BTSerial =  SoftwareSerial(rxPin, txPin);
const int photoPin = 20;
const int buzzer = 19; //buzzer to arduino pin 9
const int led = 13;
void setup() {
  // Setup serial for monitor
  Serial.begin(9600);

  // Setup DHT Sensor
  pinMode(DHTPIN, INPUT);
  
  pinMode(buzzer, INPUT); // Set buzzer - pin 9 as an output
//  pinMode(LEDPIN, INPUT);
  pinMode(led, OUTPUT);


  dht.begin();

  // Setup Serial1 for BlueTooth
  Serial1.begin(9600); // Default communication rate of the Bluetooth module
}

void loop() {
  int val = analogRead(photoPin);
  if (Serial1.available() > 0) { // Checks whether data is comming from the serial port


    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);


    float hif = dht.computeHeatIndex(f, h);
    float hic = dht.computeHeatIndex(t, h, false);

    if (val > 200) {
    tone(buzzer, 4000); // Send 1KHz sound signal...
    delay(1000); 
    noTone(buzzer);     // Stop sound...
    digitalWrite(led, HIGH);
    Serial.println("LEN ON");
    Serial1.println("LEN ON");
    delay(1000);        // ...for 1 sec
    digitalWrite(led, LOW);
    Serial.println("LEN OFF");
    Serial1.println("LEN OFF");
 
    }

    Serial.print(F(" Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.print(F("C "));
    Serial.print(f);
    Serial.print(F("F  Heat index: "));
    Serial.print(hic);
    Serial.print(F("C "));
    Serial.print(hif);
    Serial.println(F("F"));
    Serial.print("Photo : ");
    Serial.println(val);

    Serial1.print(F(" Humidity: "));
    Serial1.print(h);
    Serial1.print(F("%  Temperature: "));
    Serial1.print(t);
    Serial1.print(F("C "));
    Serial1.print(f);
    Serial1.print(F("F  Heat index: "));
    Serial1.print(hic);
    Serial1.print(F("C "));
    Serial1.print(hif);
    Serial1.println(F("F"));
    Serial1.print("Photo : ");
    Serial1.println(val);

    delay(1000);
//    digitalWrite(LEDPIN, LOW);
    delay(1000);
  }
}
