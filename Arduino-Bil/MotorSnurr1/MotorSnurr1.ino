#include <Servo.h>

#define motorPinRightDir  0//D2
#define motorPinRightSpeed 5//D1

Servo servo;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorPinRightDir, OUTPUT);
  pinMode(motorPinRightSpeed, OUTPUT);;
  servo.attach(14); //D5 on NodeMCU

  Serial.begin(115200);
}

void loop() {
  //Drivetest(motorPinLeftDir, motorPinLeftSpeed);
  //Drivetest(motorPinRightDir, motorPinRightSpeed);
  DriveDirSpeed(motorPinRightDir, motorPinRightSpeed, 1, 1023);
}
/*
  void Drivetest(int Dirpin, int Speedpin) {

  int Direction = 0;
  while (Direction <= 1)
  {
    int Speed = 600;
    while (Speed < 1020)
    {
      Speed += 25;
      DriveDirSpeed(Dirpin, Speedpin, Direction, Speed);
      delay(2200);
    }
    servo.write(100);
    Direction++;
    delay(1000);
    servo.write(0);
  }

  }
*/
void DriveDirSpeed(int Dirpin, int Speedpin, int Direction, int Speed) {
  if (Direction == 1)
    Serial.println("Framåt");
  else
    Serial.println("Bakåt");

  Serial.println("Hastighet: " + String(Speed));

  digitalWrite(Dirpin, Direction);
  analogWrite(Speedpin, Speed);
}
