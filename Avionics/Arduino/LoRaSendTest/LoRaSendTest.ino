#include <SPI.h>
#include <LoRa.h>

#define RXEN 3
#define TXEN 4

void setup()
{
    pinMode(RXEN, OUTPUT);
    pinMode(TXEN, OUTPUT);
    digitalWrite(RXEN, LOW);
    digitalWrite(TXEN, LOW);
    
    Serial.begin(115200);

    Serial.println("LoRa Sender");

    if (!LoRa.begin(915E6))
    {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
}

void loop()
{   
    digitalWrite(TXEN, HIGH);

    LoRa.beginPacket();
//    for (int i = 0; i < 3; i++)
        LoRa.print("Hello");
    LoRa.endPacket();
    
    digitalWrite(TXEN, LOW);
    delay(500);
}
