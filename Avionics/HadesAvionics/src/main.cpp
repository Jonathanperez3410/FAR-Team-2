#include <Arduino.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_GPS.h>
#include <SD.h>
#include <SPI.h>

#define Lora Serial2

#define GPSSerial Serial3
Adafruit_GPS GPS(&GPSSerial);

Adafruit_BMP280 BMP;

Adafruit_BNO055 BNO = Adafruit_BNO055(19, 0x29);

const float PRESSURE_INIT = 1015.10;

int isBMPActive, isBNOActive, isGPSActive, isLoraActive, isSDActive;

uint8_t sysCal, gyroCal, accelCal, magCal;

uint32_t timer = millis();

void deviceInit()
{
	// Initialize the BMP280
	if (!BMP.begin())
		isBMPActive = 0;
	else
		isBMPActive = 1;

	BMP.setSampling(Adafruit_BMP280::MODE_NORMAL,
					Adafruit_BMP280::SAMPLING_X2,
					Adafruit_BMP280::SAMPLING_X16,
					Adafruit_BMP280::FILTER_X16,
					Adafruit_BMP280::STANDBY_MS_500);


	// Initialize the BNO055
	if (!BNO.begin())
		isBNOActive = 0;
	else
		isBNOActive = 1;

	BNO.setExtCrystalUse(true);


	// Initialize the GPS
	GPS.begin(9600);
	GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
	GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
	GPS.sendCommand(PGCMD_ANTENNA);

	isGPSActive = 1;


	// Initialize the SD Card
	if (!SD.begin(BUILTIN_SDCARD))
		isSDActive = 0;
	else
		isSDActive = 1;
}

void setup()
{
	Serial.begin(115200);
	deviceInit();
}

void loop()
{
	char c = GPS.read();

	if (GPS.newNMEAreceived())
	{
		Serial.print(GPS.lastNMEA());
		if (!GPS.parse(GPS.lastNMEA()))
			return;
	}

	if (millis() - timer > 2000)
	{
		timer = millis();
		Serial.print("\nTime: ");

		if (GPS.hour < 10)
				Serial.print('0');
		Serial.print(GPS.hour, DEC); Serial.print(':');

		if (GPS.minute < 10)
			Serial.print('0');
		Serial.print(GPS.minute, DEC); Serial.print(':');

		if (GPS.seconds < 10)
			Serial.print('0');
		Serial.print(GPS.seconds, DEC); Serial.print('.');

		Serial.print("\nDate: ");
		Serial.print(GPS.day, DEC); Serial.print('/');
		Serial.print(GPS.month, DEC); Serial.print("/20");
		Serial.println(GPS.year, DEC);
	}
}