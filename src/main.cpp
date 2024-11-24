#include <Arduino.h>
#include "BMP280.h"
#include "Bluetooth.h"

Bluetooth bt;
BMP280 bmp280;

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println(bt.start());
  Serial.println(bmp280.start());
}

void loop() {
  
  // message from bluetooth
  if(bt.hasData()){
    Serial.print("\nÜzenet bluetooth-ról: ");
    Serial.println(bt.transmit());
  }

  bmp280.measure();

  bt.receive(bmp280.getTemperature());
  bt.receive("°C\n");

  bt.receive(bmp280.getAltitude());
  bt.receive("m\n");

  bt.receive(bmp280.getPressure());
  bt.receive("hPa\n\n");

  delay(3000);
}

// Serial.begin(baudrate) -> indít
// Serial.avaiable() -> van adat küldve?
// Serial.print(); -> ír
// Serial.readString() -> olvas