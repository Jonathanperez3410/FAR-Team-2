#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

// Hardware Serial: RX to pin 1, TX to pin 0
//#define GPSSerial Serial1
//Adafruit_GPS GPS(&GPSSerial);

// Software Serial: R

Adafruit_GPS GPS(&GPSSerial);

#define GPSECHO false

void setup()
{
    Serial.begin(115200);
    Serial.println("GPS Sensor Test\n");
    delay(1000);

    GPS.begin(9600);
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
    GPS.sendCommand(PGCMD_ANTENNA);
    delay(1000);
}

uint32_t timer = millis();

void loop()
{
    GPS.read();

    if (GPS.newNMEAreceived())
    {
        if (!GPS.parse(GPS.lastNMEA()))
            return;
    }

    if (millis() - timer > 2000)
    {
        timer = millis();

        Serial.print("Fix: "); Serial.print((int)GPS.fix);
        Serial.print(" Quality: "); Serial.println((int)GPS.fixquality);

        if (GPS.fix)
        {
            Serial.print("Location: ");
            Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
            Serial.print(", ");
            Serial.print(GPS.longitude, 4); Serial.println(GPS.lat);

            Serial.print("Speed (knots): "); Serial.println(GPS.speed);
            Serial.print("Angle: "); Serial.println(GPS.angle);
            Serial.print("Altitude: "); Serial.println(GPS.altitude);
            Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
        }
    }
}
