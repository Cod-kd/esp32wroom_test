/*
AUTHOR: @Kamiko
Discord: k.a.m.i.k.o
Version: 1.0
*/
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

class BMP280
{
private:
    Adafruit_BMP280 bmp280;
    float temperature;
    float pressure;
    float altitude;
    float local_hPa = 1013.25;

public:
    // Start useing defaults
    String start(int ADDRESS = 0x76, int SDA = 21, int SCL = 22){
        Wire.begin(SDA, SCL);

        if (!bmp280.begin(ADDRESS)) {
            return "BMP280 indítási hiba!";
        }

        // Configure BMP280
        bmp280.setSampling(Adafruit_BMP280::MODE_NORMAL,
                    Adafruit_BMP280::SAMPLING_X2,   // Temperature oversampling
                    Adafruit_BMP280::SAMPLING_X16,  // Pressure oversampling
                    Adafruit_BMP280::FILTER_X16,    // Filtering
                    Adafruit_BMP280::STANDBY_MS_500); // Standby time
        
        return "A BMP280 aktív.";
    }

    String setSeaPressure(float hPa){
        local_hPa = hPa;
        return "A tengerszintre korrigált nyomás beállítva.";
    }

    float getTemperature(){
        return temperature;
    }

    float getPressure(){
        return pressure;
    }

    float getAltitude(){
        return altitude;
    }

    void measureTemperature(){
        temperature = bmp280.readTemperature();
    }

    void measurePressure(){
        pressure = bmp280.readPressure() / 100.0F;
    }

    void measureAltitude(){
        altitude = bmp280.readAltitude(local_hPa);
    }

    void measure(){
        measureTemperature();
        measurePressure();
        measureAltitude();
    }
};