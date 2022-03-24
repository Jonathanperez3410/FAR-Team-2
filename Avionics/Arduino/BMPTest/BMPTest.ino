#include <Adafruit_BMP280.h>

#define PRESSURE_INIT 1015.10

Adafruit_BMP280 BMP;

void setup()
{
    Serial.begin(115200);

    // If the BMP did not initialize correctly, let the user know
    if (!BMP.begin())
    {
        Serial.println("BMP cannot initialize");
        while (1) delay (10);
    }

    // Otherwise, set the BMP's sampling options
    BMP.setSampling(Adafruit_BMP280::MODE_NORMAL,
                    Adafruit_BMP280::SAMPLING_X2,
                    Adafruit_BMP280::SAMPLING_X16,
                    Adafruit_BMP280::FILTER_X16,
                    Adafruit_BMP280::STANDBY_MS_500);
}

void loop()
{
    // Print out the temperature, pressure, and altitude that is read
    Serial.print(F("Temperature: "));
    Serial.print(BMP.readTemperature(), 4);
    Serial.print(F("\tPressure: "));
    Serial.print(BMP.readPressure(), 4);
    Serial.print(F("\tAltitude: "));
    Serial.println(BMP.readAltitude(PRESSURE_INIT), 4);
    delay(100);
}
