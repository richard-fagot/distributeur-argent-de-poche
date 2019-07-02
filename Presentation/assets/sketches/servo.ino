#include <Servo.h>

Servo myServo;
byte position;
byte servoPin;

void setup() {
    myServo.attach(servoPin);
    myServo.write(position);
}

void loop() {...}