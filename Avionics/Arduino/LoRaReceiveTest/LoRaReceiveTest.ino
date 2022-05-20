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

    Serial.println("LoRa Receiver");

    if (!LoRa.begin(915E6))
    {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
}

void loop()
{
    int packetSize = LoRa.parsePacket();

    char data[20];
    
    if (packetSize)
    {
        int increment = 0;
        
        while (LoRa.available())
        {
            data[increment] = (char)LoRa.read();
            increment++;
        }

        data[increment] = '\0';
        Serial.println(data);
    }
}
