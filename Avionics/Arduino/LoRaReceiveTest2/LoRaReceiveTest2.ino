#include <SoftwareSerial.h>

SoftwareSerial lora(3,2);

void setup()
{
    Serial.begin(115200);
    lora.begin(9600);

    lora.println("AT+RESET\r");
    lora.println("AT+IPR=9600\r");
    lora.println("AT+PARAMETER=7,9,4,12\r");
}

void loop()
{
    String inString;
    while (lora.available())
    {
//        if (lora.available())
//            inString += String(char(lora.read()));
        Serial.write(lora.read());
    }

    if (inString.length() > 0)
        Serial.print(inString);
}
