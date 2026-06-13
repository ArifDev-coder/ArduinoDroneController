#define joy1X A1
#define joy1Y A2
#define joy2X A3
#define joy2Y A5

void setup()
{
  Serial.begin(9600);

  // pinMode(joy1X, INPUT_PULLUP);
  // pinMode(joy1Y, INPUT_PULLUP);
  // pinMode(joy2X, INPUT_PULLUP);
  // pinMode(joy2Y, INPUT_PULLUP);
}

void loop()
{
  int valJoy1X = map(analogRead(joy1X), 0, 1023, 1023, 0);
  int valJoy1Y = map(analogRead(joy1Y), 0, 1023, 1023, 0);
  int valJoy2X = map(analogRead(joy2X), 0, 1023, 1023, 0);
  int valJoy2Y = map(analogRead(joy2Y), 0, 1023, 1023, 0);

  Serial.print("Joy01 X: "); Serial.println(valJoy1X);
  Serial.print("Joy01 Y: "); Serial.println(valJoy1Y);
  Serial.print("Joy02 X: "); Serial.println(valJoy2X);
  Serial.print("Joy02 Y: "); Serial.println(valJoy2Y);
  Serial.println();

  delay(1000);
}