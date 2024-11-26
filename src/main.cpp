/*
AUTHOR: @Kamiko
Discord: k.a.m.i.k.o
Version: 1.0
*/
#include <Arduino.h>

// include/
#include "BMP280.h"
#include "Bluetooth.h"

Bluetooth bt;
BMP280 bmp280;

void parseCommand(const String& input) {
    String commandPrefix = "set sea_hPa:";
    if (input.startsWith(commandPrefix)) {
        String valueStr = input.substring(commandPrefix.length());
        valueStr.trim();
        Serial.println(bmp280.setSeaPressure(valueStr.toFloat()));
    } else {
        Serial.println("Unknown command");
    }
}

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println(bt.start());
  Serial.println(bmp280.start());
}

void loop() {
  
  // message from bluetooth
  if(bt.hasData()){
    String command = bt.transmit();
    Serial.print("\nUtasítás bluetooth-ról: ");
    Serial.println(command);
    parseCommand(command);
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

// Serial.begin(baudrate) -> set
// Serial.avaiable() -> is there any data to send?
// Serial.print(); -> write
// Serial.readString() -> read