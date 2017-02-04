#define LED_PIN 13

void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

int calcRotate(int raw)
{
  return (raw - 277) / 2.48 - 90;
}

void printLog(int x, int y, int z)
{
  Serial.print("X:");
  Serial.print(x);
  Serial.print(" ");
  Serial.print("Y:");
  Serial.print(y);
  Serial.print(" ");
  Serial.print("Z:");
  Serial.print(z);
  Serial.println(" ");
}

void loop()
{
  int i;
  long x, y, z;
  long threshold = 180; // 振ったことを検出するしきい値

  // 50回センサ値を読み込んで平均を算出
  x = y = z = 0;
  for (i = 0; i < 50; i++) {
    x = x + analogRead(3); // Ｘ軸
    y = y + analogRead(4); // Ｙ軸
    z = z + analogRead(5); // Ｚ軸
  }
  x = x / 50;
  y = y / 50;
  z = z / 50;

  int rotateX = calcRotate(x);
  int rotateY = calcRotate(y);
  int rotateZ = calcRotate(z);

  printLog(rotateX, rotateY, rotateZ);

  if (rotateX > threshold || rotateY > threshold || rotateZ > threshold) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  delay(100);
}
