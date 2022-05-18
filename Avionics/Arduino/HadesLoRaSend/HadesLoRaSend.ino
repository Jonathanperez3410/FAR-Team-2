#include <SPI.h>
#include <LoRa.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop()
{
  int sensorVal = analogRead(A0);
  
  LoRa.beginPacket();
  LoRa.print(sensorVal);
  LoRa.endPacket();
}
