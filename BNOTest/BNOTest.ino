#include <Adafruit_BNO055.h>

Adafruit_BNO055 BNO = Adafruit_BNO055(19, 0x29);

uint8_t sys, gyro, accel, mag;

void setup()
{
    Serial.begin(115200);
    Serial.println("Orientation Sensor Test"); Serial.println("");
    
    if (!BNO.begin())
    {
        Serial.print("No BMO055 Detected...");
        while(1);
    }

    delay(1000);
    
    BNO.setExtCrystalUse(true);
}

void loop()
{
    imu::Vector<3> euler = BNO.getVector(Adafruit_BNO055::VECTOR_EULER);
    imu::Vector<3> accel = BNO.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    imu::Vector<3> magnet = BNO.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
    imu::Vector<3> gyro = BNO.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
    imu::Vector<3> linAccel = BNO.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
    imu::Vector<3> grav = BNO.getVector(Adafruit_BNO055::VECTOR_GRAVITY);

    if (getCalStatus())
    {
        printVector(euler);

//        printQuat();
//        printVector(accel);
//        printVector(magnet);
//        printVector(gyro);
//        printVector(linAccel);
//        printVector(grav);
//        printTemp();
    }
      
    delay(100);
}

int getCalStatus(void)
{
    sys = gyro = accel = mag = 0;
    BNO.getCalibration(&sys, &gyro, &accel, &mag);

    if (accel == 3 && gyro == 3 && mag == 3)
        return 1;
    else
    {
//        Serial.print("S:");
//        Serial.print(sys, DEC);
        Serial.print(" G:");
        Serial.print(gyro);
        Serial.print(" A:");
        Serial.print(accel, DEC);
        Serial.print(" M:");
        Serial.println(mag, DEC);
        return 0;
    }
}

void printVector(imu::Vector<3> vector)
{
  Serial.print("X: ");
  Serial.print(vector.x(), 4);
  Serial.print("\tY: ");
  Serial.print(vector.y(), 4);
  Serial.print("\tZ: ");
  Serial.println(vector.z(), 4);
}

void printQuat()
{
  imu::Quaternion quat = BNO.getQuat();
  
  Serial.print("qW: ");
  Serial.print(quat.w(), 4);
  Serial.print("\tqX: ");
  Serial.print(quat.x(), 4);
  Serial.print("\tqY: ");
  Serial.print(quat.y(), 4);
  Serial.print("\tqZ: ");
  Serial.println(quat.z(), 4);
}

void printTemp()
{
  int8_t temp = BNO.getTemp();
  
  Serial.print("\tTemp: ");
  Serial.print(temp);
  Serial.println(" C");
}
