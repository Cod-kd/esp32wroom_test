/*
AUTHOR: @Kamiko
Discord: k.a.m.i.k.o
Version: 1.0
*/
#include "BluetoothSerial.h"

class Bluetooth
{
private:
    BluetoothSerial SerialBT;

public:
    String start(String device_name = "ESP32_BT"){
        SerialBT.begin(device_name);
        return "Bluetooth aktív.";
    }

    bool hasData(){
        return SerialBT.available();
    }
    
    String transmit(){
        return SerialBT.readString();
    }

    void receive(float data){
        SerialBT.print(data);
    }
    
    void receive(String data){
        SerialBT.print(data);
    }
};