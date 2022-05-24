#include <SoftwareSerial.h>

#define lora Serial2

void setup()
{
    Serial.begin(115200);
    lora.begin(115200);
    lora.println("AT+RESET\r");
    lora.println("AT+IPR=115200\r");
}

void loop()
{
    String cmd = "AT+SEND=0,5,Hello\r";
    lora.println(cmd);

    while(lora.available())
        Serial.write(lora.read());
    Serial.println();
    Serial.println(cmd);
    delay(1000);
}
