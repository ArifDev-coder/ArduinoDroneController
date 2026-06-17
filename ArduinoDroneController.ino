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
}

ControlData data;

void resetData()
{
  data.throttle = 0;
  data.yaw = 0;
  data.pitch = 0;
  data .roll = 0;
}

void setup()
{
  resetData();

  Serial.begin(9600);


}

// Remapping value mentah joystick
int mapJoystickValue(int val, int lower, int middle, int, upper, bool isReverse = false)
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

  return { isReverse ? 255 - val : val };
}

void loop()
{
  data.throttle = mapJoystickValue(analogRead(X2), int lower, int middle, int, int);
  data.yaw = mapJoystickValue(analogRead(Y2), int lower, int middle, int, int);
  data.pitch = mapJoystickValue(analogRead(X1), int lower, int middle, int, int);
  data.roll = mapJoystickValue(analogRead(Y1), int lower, int middle, int, int);
}