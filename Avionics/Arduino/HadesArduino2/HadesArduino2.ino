#include <Adafruit_BNO055.h>
#include <Adafruit_BMP280.h>

#define PRESSURE_INIT 1015.10

// Create variables for the BNO and BMP
// The BNO's I2C address is pulled up to 0x29 to avoid conflict with the BMP
Adafruit_BNO055 BNO = Adafruit_BNO055(19, 0x29);
Adafruit_BMP280 BMP;

// Create variables for the calibration status of the BNO
uint8_t sysCal, gyroCal, accelCal, magCal;

void setup()
{
    // Connect to the serial port and initialize the sensors
    Serial.begin(115200);
    bnoInit();
    bmpInit();
}

void loop() 
{
    bnoData();
    bmpData();
    delay(100);
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

int bnoCalStatus()
{
    sysCal = gyroCal = accelCal = magCal = 0;
    BNO.getCalibration(&sysCal, &gyroCal, &accelCal, &magCal);

    if (gyroCal == 3 && accelCal == 3 && magCal == 3)
        return 1;
    else
    {
        sendBNOCalStatus();
        return 0;
    }
}

void bnoData()
{
    imu::Vector<3> euler = BNO.getVector(Adafruit_BNO055::VECTOR_EULER);
    imu::Vector<3> accel = BNO.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    imu::Vector<3> mag = BNO.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
    imu::Vector<3> gyro = BNO.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
    imu::Vector<3> linAccel = BNO.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
    imu::Vector<3> grav = BNO.getVector(Adafruit_BNO055::VECTOR_GRAVITY);

    if (bnoCalStatus())
    {
        sendBNOVector(euler, "bno_euler");
        sendBNOVector(accel, "bno_accel");
        sendBNOVector(mag, "bno_mag");
        sendBNOVector(gyro, "bno_gyro");
        sendBNOVector(linAccel, "bno_linAccel");
        sendBNOVector(grav, "bno_grav");
        sendData("bno_temp", (String)BNO.getTemp());
    }
}

void bmpData()
{
    sendData("bmp_temp", (String)BMP.readTemperature());
    sendData("bmp_pressure", (String)BMP.readPressure());
    sendData("bmp_altitude", (String)BMP.readAltitude(PRESSURE_INIT));
}

void sendBNOVector(imu::Vector<3> vector, String prefix)
{
    String vectorStr = (String)vector.x() + "," +
                       (String)vector.y() + "," +
                       (String)vector.z();

    sendData(prefix, vectorStr);
}

void sendBNOCalStatus()
{
    String calStatus = (String)gyroCal + "," +
                       (String)accelCal + "," +
                       (String)magCal;

    sendData("bno_cal_status", calStatus);
}

void sendData(String prefix, String data)
{
    Serial.println("*" + prefix + "," + data + "#");
}
