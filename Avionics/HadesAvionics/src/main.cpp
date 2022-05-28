#include <Arduino.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_GPS.h>
#include <SD.h>
#include <SPI.h>

// The buzzer is connected to pin 2
const int BUZZER = 2;

// The GPS is connected to the Teensy's Serial3 (Pins 7 & 8)
Adafruit_GPS GPS(&Serial3);
// #define GPSSerial Serial3
// Adafruit_GPS GPS(&GPSSerial);

// The BMP and BNO are connected to the Teensy's SPI0 (Pins 18 & 19)
// The BNO's ADR pin is pulled high, changing the address, to avoid conflicts with the BMP
Adafruit_BMP280 BMP;
Adafruit_BNO055 BNO = Adafruit_BNO055(19, 0x29);

// A buffer for the file that the data is being saved on
File dataOut;

// Stores the activation status of each of the sensors
int isSDActive, isGPSActive, isBMPActive, isBNOActive;

// Stores the calibration status of the BNO
uint8_t sysCal, gyroCal, accelCal, magCal;

// In debug mode, the avionics will push certain data through the USB port
const int DEBUG_MODE = 1;

void sdInit();
void gpsInit();
void bmpInit();
void bnoInit();

void writeBMPData();
void writeBNOData();

void getTime();
void happyBeep();
void sadBeep();
void numBeeps(int beeps);

void setup()
{
    if (DEBUG_MODE)
        Serial.begin(115200);

    pinMode(BUZZER, OUTPUT);

    // sdInit();
    gpsInit();
    // bmpInit();
    // bnoInit();
}

void loop()
{
    // char c = GPS.read();
    GPS.read();

    if (GPS.newNMEAreceived())
    {
        Serial.print(GPS.lastNMEA());
        if (!GPS.parse(GPS.lastNMEA()))
            return;
    }

    if (GPS.fix)
    {
        Serial.println("FIX");
        delay(100);
    }

}

void sdInit()
{
    numBeeps(1);
    delay(500);

    if (!SD.begin(BUILTIN_SDCARD))
    {
        isSDActive = 0;
        sadBeep();
    }
    else
    {
        isSDActive = 1;
        happyBeep();
    }

    delay(1000);
}

void gpsInit()
{
    numBeeps(2);
    delay(500);

    GPS.begin(9600);
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
    GPS.sendCommand(PGCMD_ANTENNA);

    isGPSActive = 1;
    happyBeep();

    delay(1000);

    /*
    while (1)
    {
        GPS.read();
        if (GPS.newNMEAreceived())
        {
            Serial.print(GPS.lastNMEA());
            GPS.parse(GPS.lastNMEA());
        }

        if (GPS.fix)
            return;

        Serial.println("NO FIX");
        delay(500);
    }
    */
}

void bmpInit()
{
    numBeeps(3);
    delay(500);

    if (!BMP.begin())
    {
        isBMPActive = 0;
        sadBeep();
    }
    else
    {
        isBMPActive = 1;
        happyBeep();
    }

    BMP.setSampling(Adafruit_BMP280::MODE_NORMAL,
                    Adafruit_BMP280::SAMPLING_X2,
                    Adafruit_BMP280::SAMPLING_X16,
                    Adafruit_BMP280::FILTER_X16,
                    Adafruit_BMP280::STANDBY_MS_500);

    delay(1000);
}

void bnoInit()
{
    numBeeps(4);
    delay(500);

    if (!BNO.begin())
    {
        isBNOActive = 0;
        sadBeep();
    }
    else
    {
        isBNOActive = 1;
        happyBeep();
    }

    BNO.setExtCrystalUse(true);

    while (sysCal != 3)
    {
        sysCal = gyroCal = accelCal = magCal = 0;
        BNO.getCalibration(&sysCal, &gyroCal, &accelCal, &magCal);
    }

    delay(1000);
}

void writeBMPData()
{
    dataOut.print((String)BMP.readTemperature() + ",");
    dataOut.print((String)BMP.readPressure() + ",");
}

void writeBNOData()
{
    sysCal = gyroCal = accelCal = magCal = 0;
    BNO.getCalibration(&sysCal, &gyroCal, &accelCal, &magCal);

    imu::Vector<3> euler = BNO.getVector(Adafruit_BNO055::VECTOR_EULER);
    imu::Vector<3> gyro = BNO.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
    imu::Vector<3> accel = BNO.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);

    if (sysCal == 3)
    {
        dataOut.print((String)euler.x() + ",");
        dataOut.print((String)euler.y() + ",");
        dataOut.print((String)euler.z() + ",");

        dataOut.print((String)gyro.x() + ",");
        dataOut.print((String)gyro.y() + ",");
        dataOut.print((String)gyro.z() + ",");

        dataOut.print((String)accel.x() + ",");
        dataOut.print((String)accel.y() + ",");
        dataOut.print((String)accel.z() + ",");
    }
    else
    {
        for (int i = 0; i < 9; i++)
            dataOut.print("NO_BNO_CAL,");
    }
}

void getTime()
{
    // GPS.read();
    // if (GPS.newNMEAreceived())
    // 	if (!GPS.parse(GPS.lastNMEA()))
    // 		return;

    Serial.print(GPS.year, DEC); Serial.print("-");
    Serial.print(GPS.month, DEC); Serial.print("-");
    Serial.print(GPS.day, DEC); Serial.print("-");
    Serial.println("");
}

void happyBeep()
{
    tone(BUZZER, 1568);
    delay(250);
    tone(BUZZER, 2093);
    delay(250);
    noTone(BUZZER);
}

void sadBeep()
{
    tone(BUZZER, 1480);
    delay(250);
    noTone(BUZZER);
    delay(50);
    tone(BUZZER, 1480);
    delay(250);
    noTone(BUZZER);
}

void numBeeps(int beeps)
{
    for (int i = 0; i < beeps; i++)
    {
        tone(BUZZER, 1800);
        delay(250);
        noTone(BUZZER);
        delay(250);
    }
}