#include <Servo.h>

Servo servo;
void setup() {

  servo.attach(3);
  servo.write(180);
  delay(1000);
  servo.write(0);
  delay(1000);
  servo.write(180);
  delay(1000);
  servo.detach();
}

void loop() {
  // put your main code here, to run repeatedly:

}
