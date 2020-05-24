#include <Servo.h>

Servo servo;

void setup() {
  Serial.begin(115200);
  servo.attach(14);
}

void loop() {
  servo.write(90);
  Serial.print("Vrider!");
  delay(1000);
  servo.write(-90);
  Serial.println("Vrider");
  delay(1000);
}
