#include <SoftwareSerial.h>

//SoftwareSerial lora(7, 8);
#define lora Serial3

void setup()
{
//    Serial.begin(115200);
    lora.begin(115200);
}

void loop()
{
//    lora.print("Hello");

    lora.print("AT\r\n");

    delay(500);
}
