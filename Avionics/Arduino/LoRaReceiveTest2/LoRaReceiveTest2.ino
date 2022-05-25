#include <SoftwareSerial.h>

SoftwareSerial Lora(3, 2);

String incomingString;

void setup()
{
    Lora.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    if (Serial.available())
    {
        incomingString = Serial.readString();
        if(incomingString.indexOf("Testing!") == 0)
        {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
        }
    }
}
