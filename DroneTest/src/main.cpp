#include <Arduino.h>
#include <RF24.h>
#include <SPI.h>

// Radio CE, CSN
RF24 radio(7, 10);

// Pipe Address
const byte pipe_address[6] = "12301";

struct DataControlPackage
{
  byte throttle;
  byte yaw;
  byte pitch;
  byte roll;
};

DataControlPackage receivedData;

void setup()
{
  Serial.begin(9600);

  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(0, pipe_address);
  radio.startListening();
}

void loop()
{
  if (radio.available())
  {
    radio.read(&receivedData, sizeof(DataControlPackage));

    Serial.print("Throttle: ");
    Serial.print(receivedData.throttle);
    Serial.print(" | Roll: ");
    Serial.print(receivedData.roll);
    Serial.print(" | Pitch: ");
    Serial.print(receivedData.pitch);
    Serial.print(" | Yaw: ");
    Serial.println(receivedData.yaw);
  }

  delay(10);
}