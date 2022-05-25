#include <SoftwareSerial.h>

#define Lora Serial3

unsigned long lastTransmission;
const int interval = 1000;

void setup()
{
    Lora.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    if (millis() > lastTransmission + interval)
    {
        Lora.println("AT+SEND=0,8,Testing!\r");
        digitalWrite(LED_BUILTIN ,HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
        lastTransmission = millis();
    }
}
