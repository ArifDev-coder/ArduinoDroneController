#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);
const byte address[6] = "00001";

uint32_t lastCounter = 0;
uint32_t received = 0;
uint32_t expected = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setAutoAck(false);          // matikan ack
  radio.setChannel(100);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    uint32_t incoming;
    radio.read(&incoming, sizeof(incoming));

    received++;
    expected = incoming - lastCounter - 1; // paket yang lompat/hilang

    Serial.print("Diterima: ");
    Serial.print(incoming);
    if (expected > 0 && incoming > lastCounter) {
      Serial.print("  <-- LOST ");
      Serial.print(expected);
      Serial.print(" paket!");
    }
    Serial.println();

    lastCounter = incoming;
  }
}