#include <Arduino.h>
#include <RF24.h>
#include <SPI.h>

// Pin analog pada joystick
// From right to left joystick.
const byte X1 = A1;
const byte Y1 = A2;
const byte X2 = A3;
const byte Y2 = A5;

// Struktur awal variable Controller
struct ControlData
{
  byte throttle;
  byte yaw;
  byte pitch;
  byte roll;
};

ControlData data;

// Radio CE, CSN
RF24 radio(10, 9);

const byte pipe_addres[6] = "12301";

void resetData()
{
  data.throttle = 0;
  data.yaw = 127;
  data.pitch = 127;
  data.roll = 127;
}

void setup()
{
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipe_addres);
  radio.stopListening();

  resetData();

  Serial.begin(9600);
}

// Remapping value mentah joystick
int mapJoystickValue(int val, int lower, int middle, int upper, bool isReverse = false)
{
  val = constrain(val, lower, upper);

  if (val < middle)
  {
    val = map(val, lower, middle, 0, 128);
  }
  else
  {
    val = map(val, middle, upper, 128, 255);
  }

  return {isReverse ? 255 - val : val};
}

void loop()
{
  data.throttle = mapJoystickValue(analogRead(X2), 0, 390, 1014, true);
  data.yaw = mapJoystickValue(analogRead(Y2), 0, 408, 1007, true);
  data.pitch = mapJoystickValue(analogRead(X1), 0, 386, 911, true);
  data.roll = mapJoystickValue(analogRead(Y1), 0, 413, 991, true);

  Serial.print(data.throttle); Serial.print(",");
  Serial.print(data.yaw);      Serial.print(",");
  Serial.print(data.pitch);    Serial.print(",");
  Serial.println(data.roll);

  radio.write(&data, sizeof(ControlData));
}