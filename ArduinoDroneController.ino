#define joy1X A1
#define joy1Y A2
#define joy2X A3
#define joy2Y A5

const int MID_1X = 350;
const int MID_1Y = 366;
const int MID_2X = 345;
const int MID_2Y = 358;

const int MIN_VAL = 0;
const int MAX_VAL = 890;

void setup()
{
  Serial.begin(9600);

  // pinMode(joy1X, INPUT_PULLUP);
  // pinMode(joy1Y, INPUT_PULLUP);
  // pinMode(joy2X, INPUT_PULLUP);
  // pinMode(joy2Y, INPUT_PULLUP);
}

int normalizeJoystick(int raw, int midPoint, bool reverse = false )
{
  int out;

  if (raw < midPoint) 
  {
    out = map(raw, MIN_VAL, midPoint, -512, 0);
  }
  else 
  {
    out = map(raw, midPoint, MAX_VAL, 0, 511);
  }

  out = constrain(out, -512, 511);

  if (reverse)
  {
    out = -out;
  }

  return out;
}

void loop()
{
  // int valJoy1X = map(analogRead(joy1X), 0, 863, 1023, 0);
  // int valJoy1Y = map(analogRead(joy1Y), 0, 877, 1023, 0);
  // int valJoy2X = map(analogRead(joy2X), 0, 899, 1023, 0);
  // int valJoy2Y = map(analogRead(joy2Y), 0, 898, 1023, 0);

  // Serial.print("Joy01 X: "); Serial.println(valJoy1X);
  // Serial.print("Joy01 Y: "); Serial.println(valJoy1Y);
  // Serial.print("Joy02 X: "); Serial.println(valJoy2X);
  // Serial.print("Joy02 Y: "); Serial.println(valJoy2Y);
  // Serial.println();

  int totalRawX1 = 0;
  int totalRawY1 = 0;
  int totalRawX2 = 0;
  int totalRawY2 = 0;

  for (int i = 0; i < 10; i++)
  {
    int rawX1 = analogRead(joy1X);
    int rawY1 = analogRead(joy1Y);
    int rawX2 = analogRead(joy2X);
    int rawY2 = analogRead(joy2Y);

    totalRawX1 += rawX1;
    totalRawY1 += rawY1;
    totalRawX2 += rawX2;
    totalRawY2 += rawY2;
  }

  int finalRawX1 = totalRawX1 / 10;
  int finalRawY1 = totalRawY1 / 10;
  int finalRawX2 = totalRawX2 / 10;
  int finalRawY2 = totalRawY2 / 10;

  int pitch = normalizeJoystick(finalRawX1, MID_1X, true);
  int roll = normalizeJoystick(finalRawY1, MID_1Y, true);
  int throttle = normalizeJoystick(finalRawX2, MID_2X, true);
  int yaw = normalizeJoystick(finalRawY2, MID_2Y, true);

  char buffer[100];
  sprintf(buffer, "NORM : pitch:%4d roll:%4d | throttle:%4d yaw:%4d || RAW : J1X:%4d J1Y:%4d | J2X:%4d J2Y:%4d", 
          pitch, roll, throttle, yaw, finalRawX1, finalRawY1, finalRawX2, finalRawY2);
  Serial.println(buffer);
}
