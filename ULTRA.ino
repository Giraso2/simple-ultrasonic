#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define trigPin 5
#define echoPin 6
#define servoPin 7

Servo myServo;

long duration;
float distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myServo.attach(servoPin);
  myServo.write(0);   

  lcd.init();
  lcd.backlight();
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 30000);

  lcd.clear();

  if (duration == 0) {
    lcd.setCursor(0, 0);
    lcd.print("No object");
    myServo.write(0);
  } 
  else {
    distance = (duration * 0.0343) / 2;

    lcd.setCursor(0, 0);
    lcd.print("Distance:");
    lcd.setCursor(0, 1);
    lcd.print(distance);
    lcd.print(" cm");

    
    if (distance >= 7 && distance <= 30) {
      myServo.write(90);
    } 
    else {
      myServo.write(0);
    }
  }

  delay(500);
}
