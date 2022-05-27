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

File dataOut;

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

void setup()
{
	Serial.begin(115200);
	
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
	{
		isSDActive = 1;
		dataOut = SD.open("data.csv", FILE_WRITE);
	}
}

void loop()
{
	dataOut = SD.open("data.fuck", FILE_WRITE);

	writeBNOData();
	writeBMPData();

	dataOut.println();
	dataOut.close();
	delay(500);
}