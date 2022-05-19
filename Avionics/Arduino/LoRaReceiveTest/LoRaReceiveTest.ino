#include <SPI.h>
#include <LoRa.h>

#define RXEN 3
#define TXEN 4

void setup()
{
    pinMode(RXEN, OUTPUT);
    pinMode(TXEN, OUTPUT);
    digitalWrite(RXEN, HIGH);
    digitalWrite(TXEN, LOW);
    
    Serial.begin(115200);
    while (!Serial);

    Serial.println("LoRa Receiver");

    if (!LoRa.begin(915E6))
    {
        Serial.println("Starting LoRa failed!");
        while (1);
    }

    pinMode(7, OUTPUT);
}

void loop()
{
    int packetSize = LoRa.parsePacket();
    
    if (packetSize)
    {
        Serial.print("Received packet '");
        digitalWrite(7, HIGH);

        while (LoRa.available())
            Serial.print((char)LoRa.read());

        Serial.print("' with RSSI ");
        Serial.println(LoRa.packetRssi());

        delay(100);
        digitalWrite(7, LOW);
    }
}
