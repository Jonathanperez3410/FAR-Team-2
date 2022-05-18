#include <SPI.h>
#include <LoRa.h>

#define MLPWM 17
#define MLDIR 15
#define MRPWM 16
#define MRDIR 14

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];

int motorL = 0;
int motorR = 0;

boolean newData = false;

void setup()
{
   /// Serial.begin(9600);
   // while (!Serial);

    pinMode(MLPWM, OUTPUT);
    pinMode(MLDIR, OUTPUT);
    pinMode(MRPWM, OUTPUT);
    pinMode(MRDIR, OUTPUT);

    digitalWrite(MLPWM, LOW);
    digitalWrite(MLDIR, LOW);
    digitalWrite(MRPWM, LOW);
    digitalWrite(MRDIR, LOW);
    
    if (!LoRa.begin(915E6))
    {
      //  Serial.println("Starting LoRa failed!");
        while (1);
    }
}

void loop()
{

//    recieveData();
//    showParsedData();
    

    // try to parse packet
    int packetSize = LoRa.parsePacket();
    if (packetSize)
    {
        // read packet
        while (LoRa.available())
            parseData(LoRa.readString());
    }
    
}

/*
void recieveData() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
    int packetSize = LoRa.parsePacket();
    
    while (packetSize && newData == false) {
        rc = (char)LoRa.readString();
        Serial.println(LoRa.readString());

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
} */

void parseData(String dataStr)
{
    char dataBuffer[numChars];
    dataStr.toCharArray(dataBuffer, numChars);
    
    sscanf(dataBuffer, "%d,%d", &motorL, &motorR);

//    Serial.print(motorL + " " + motorR);
    if (motorL >= 256)
    {
        analogWrite(MLPWM, map(motorL, 256, 511, 0, 255));
        digitalWrite(MLDIR, HIGH);
    }
    else if (motorL <= 255)
    {
        analogWrite(MLPWM, motorL);
        digitalWrite(MLDIR, LOW);
    }
    
    if (motorR >= 256)
    {
        analogWrite(MRPWM, map(motorR, 256, 511, 0, 255));
        digitalWrite(MRDIR, LOW);
    }
    else if (motorR <= 255)
    {
        analogWrite(MRPWM, motorR);
        digitalWrite(MRDIR, HIGH); 
    }
}


/*
void showParsedData() {

  Serial.print("L: ");
  Serial.print(motorL);
  Serial.print(" R: ");
  Serial.println(motorR);

  if (motorL >= 256) {
    analogWrite(MRPWM, map(motorL, 256, 511, 0, 255));
    digitalWrite(MRDIR, HIGH);
    
  } else if (motorL <= 255) {
    analogWrite(MRPWM, motorL);
    digitalWrite(MRDIR, LOW);
    
  }
  if (motorR >= 256) {
    analogWrite(MLPWM, map(motorR, 256, 511, 0, 255));
    digitalWrite(MLDIR, HIGH);
    
  } else if (motorR <= 255) {
    analogWrite(MLPWM, motorR);
    digitalWrite(MLDIR, LOW);
    
  }
} */
