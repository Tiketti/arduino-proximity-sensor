/*
HC-SR04 Ping distance sensor
VCC to arduino 5v
GND to arduino GND
Echo to Arduino pin 3
Trig to Arduino pin 2
*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11 , 12);

#define trigPin 3
#define echoPin 2

long pollingInterval = 500;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.begin(16, 2);
  lcd.blink();
  lcd.setCursor(0,0);
  lcd.print("DISTANCE:");
}

long getPromiximityDuration () {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  return pulseIn(echoPin, HIGH);
}

long calculateDistance (long duration) {
  return duration * 0.034 / 2;
}

void outputDistance (long distance) {
  // clear line
  lcd.setCursor(0,1);
  lcd.print("       ");
  
  lcd.setCursor(0,1);
  lcd.print(String(distance) + " cm");
  lcd.setCursor(15,1);
}

void loop() {
  long duration, distance;

  duration = getPromiximityDuration();  
  distance = calculateDistance(duration);

  if (distance >= 200 || distance <= 0) {
    Serial.println(0);
  }
  else {
    Serial.println(distance);
    outputDistance(distance);
  }
  
  delay(pollingInterval);
}
