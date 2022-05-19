#include <SPI.h>
#include <LoRa.h>

#define RXEN 3
#define TXEN 4

void setup()
{
    pinMode(RXEN, OUTPUT);
    pinMode(TXEN, OUTPUT);
    digitalWrite(RXEN, LOW);
    digitalWrite(TXEN, HIGH);
    
    Serial.begin(115200);
    while (!Serial);

    Serial.println("LoRa Sender");

    if (!LoRa.begin(915E6))
    {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
}

void loop()
{   
    LoRa.beginPacket();
    LoRa.print("HellHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloo!");
    LoRa.endPacket();
    delay(500);
}
