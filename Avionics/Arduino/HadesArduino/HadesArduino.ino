#include <SoftwareSerial.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_GPS.h>

// Create variables for the BNO and BMP
// The BNO's I2C address is pulled up to 0x29 to avoid conflict with the BMP
Adafruit_BNO055 BNO = Adafruit_BNO055(19, 0x29);
Adafruit_BMP280 BMP;

// Create variables for the software serial connection and the GPS
// RX to pin 7 and TX to pin 8
#define GPSSerial Serial1
Adafruit_GPS GPS(&GPSSerial);

// Create variables for the calibration status of the BNO
uint8_t sysCal, gyroCal, accelCal, magCal;

// Define the initial atmospheric pressure for the BMP
#define PRESSURE_INIT 1015.10

// Create interrupt timers for each sensor
uint32_t bnoTimer = millis();
uint32_t bmpTimer = millis();
uint32_t gpsTimer = millis();

void setup()
{
    // Connect to the serial port and initialize the sensors
    Serial.begin(115200);
    bnoInit();
//    bmpInit();
    gpsInit();
}

void loop() 
{
    bnoData();
//    bmpData();
    gpsData();
}

void bnoInit()
{
    // If the BNO cannot be initialized, throw an error
    if (!BNO.begin())
    {
        sendData("command", "bno_init_bad");
        while (1) delay (10);
    }

    // Set external crystal use on for the BNO, look into this
    BNO.setExtCrystalUse(true);
}

void bmpInit()
{
    // If the BMP cannot be initialized, throw an error
    if (!BMP.begin())
    {
        sendData("command", "bmp_init_bad");
        while (1) delay (10);
    }

    // Set the sampling for the BMP, as per the device instructions
    BMP.setSampling(Adafruit_BMP280::MODE_NORMAL,
                    Adafruit_BMP280::SAMPLING_X2,
                    Adafruit_BMP280::SAMPLING_X16,
                    Adafruit_BMP280::FILTER_X16,
                    Adafruit_BMP280::STANDBY_MS_500);

    sendData("command", "bmp_init_good");
}

void gpsInit()
{
    // Open up the GPS and set the default options
    GPS.begin(9600);
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
    GPS.sendCommand(PGCMD_ANTENNA);

    sendData("command", "gps_init_good");
}

void bnoData()
{
    if (millis() - bnoTimer > 100)
    {
        bnoTimer = millis();
        
        sysCal = gyroCal = accelCal = magCal = 0;
        BNO.getCalibration(&sysCal, &gyroCal, &accelCal, &magCal);
    
        String calStatus = (String)gyroCal + "," +
                           (String)accelCal + "," +
                           (String)magCal;
    
        sendData("bno_cal_status", calStatus);
        
        imu::Vector<3> euler = BNO.getVector(Adafruit_BNO055::VECTOR_EULER);
        imu::Vector<3> accel = BNO.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
        imu::Vector<3> mag = BNO.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
        imu::Vector<3> gyro = BNO.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
        imu::Vector<3> linAccel = BNO.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
        imu::Vector<3> grav = BNO.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
    
        if (gyroCal == 3 && magCal == 3)
        {
            sendBNOVector(euler, "bno_euler");
//            sendBNOVector(accel, "bno_accel");
//            sendBNOVector(mag, "bno_mag");
//            sendBNOVector(gyro, "bno_gyro");
//            sendBNOVector(linAccel, "bno_linAccel");
//            sendBNOVector(grav, "bno_grav");
//            sendData("bno_temp", (String)BNO.getTemp());
        }
    }
}

void bmpData()
{
    if (millis() - bmpTimer > 100)
    {
        bmpTimer = millis();

        String bmpData = (String)BMP.readTemperature() + "," +
                         (String)BMP.readPressure() + "," +
                         (String)BMP.readAltitude(PRESSURE_INIT);

        sendData("bmp_data", bmpData);
    }
}

void gpsData()
{
    GPS.read();
    
    if (GPS.newNMEAreceived())
        if (!GPS.parse(GPS.lastNMEA()))
            return;

    if (millis() - gpsTimer > 100)
    {
        gpsTimer = millis();

        sendData("gps_fix_status", String((int)GPS.fix));
    
        if (GPS.fix)
        {
            String gpsData = 
                String(GPS.latitude, 4) + "," + GPS.lat + "," + 
                String(GPS.longitude, 4) + "," + GPS.lon;
            
            sendData("gps_data", gpsData);
        }
    }
}

void sendBNOVector(imu::Vector<3> vector, String prefix)
{
    String vectorStr = (String)vector.x() + "," +
                       (String)vector.y() + "," +
                       (String)vector.z();

    sendData(prefix, vectorStr);
}

void sendData(String prefix, String data)
{
    Serial.println("*" + prefix + "," + data + "#");
}
