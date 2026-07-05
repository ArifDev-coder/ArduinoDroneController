#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(10, 9);
const byte address[6] = "00001";

uint32_t counter = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setAutoAck(false);          // matikan ack
  radio.setChannel(100);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address);
  radio.stopListening();
}

void loop() {
  radio.write(&counter, sizeof(counter));
  Serial.print("Sent: ");
  Serial.println(counter);
  counter++;
  delay(100); // biar gampang diamati, nanti bisa dipercepat
}