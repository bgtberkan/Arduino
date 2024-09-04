#include <Servo.h>
#define pirPin 8
#define servoPin 9
#define ledPin 7
Servo motor;
void setup() {
  motor.attach(servoPin);
  pinMode(pirPin , INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
 int hareket = digitalRead(pirPin);
 if(hareket == HIGH)
 {
  digitalWrite(ledPin, HIGH);
  motor.write(150);
  delay(2000);
  motor.write(90);
  digitalWrite(ledPin, LOW);
 }
 else 
 {
  motor.write(90);
 }

}
