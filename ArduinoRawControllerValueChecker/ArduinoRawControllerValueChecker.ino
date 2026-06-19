#include <SPI.h>

// Pin analog pada joystick
// From right to left joystick.
const byte X1 = A1;
const byte Y1 = A2;
const byte X2 = A3;
const byte Y2 = A5;

struct Value
{
  int min = 1024;
  int max = 0;
  int raw = 0;
};

Value valX1, valY1, valX2, valY2;

void setup() {
  Serial.begin(9600);


    for (int i = 0; i < 10; i++) {
      analogRead(X1); analogRead(X2);
      analogRead(Y1); analogRead(Y2);
      delay(10);
    }
}

void minMaxRawChecker(const char* label, Value& val, int pin)
{
  val.raw = analogRead(pin);

  if (val.raw < val.min)
  {
    val.min = val.raw;
  }
  
  if (val.raw > val.max)
  {
    val.max = val.raw;
  }

  Serial.print(label);
  Serial.print(" raw="); Serial.print(val.raw);
  Serial.print(" min="); Serial.print(val.min);
  Serial.print(" max="); Serial.print(val.max);
  Serial.println();
}

void loop() {
  minMaxRawChecker("throttle", valX2, X2);  //  Mid: 394  Min: 0  Max: 1014
  minMaxRawChecker("yaw", valY2, Y2);       //  Mid: 408  Min: 0  Max: 1007
  minMaxRawChecker("pitch", valX1, X1);     //  Mid: 386  Min: 0  Max: 911
  minMaxRawChecker("roll", valY1, Y1);      //  Mid: 413  Min: 0  Max: 991

  Serial.println("----------");
  delay(200);
}
