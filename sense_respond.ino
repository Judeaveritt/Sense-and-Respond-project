/*
 * HC-SR04 example sketch
 *
 * https://create.arduino.cc/projecthub/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-036380
 *
 * by Isaac100
 */

#include <DHT.h>
#include <LiquidCrystal.h>

const int rs = 7;
const int en = 8;
const int d4 = 9;
const int d5 = 10;
const int d6 = 11;
const int d7 = 12;
const int buzzerPin = 3;
const float inchesPerMicrosecond = 0.0135;
const int stopdistance = 10;
const int slowdistance = 36;



const int pause = 5000;

const int trigPin = 4;
const int echoPin = 2;

float duration, distance;
// set up objects


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {


  //initialize the 16x2 LCD
  lcd.begin(16,2);
  pinMode(buzzerPin, OUTPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}





void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * inchesPerMicrosecond)/2;
 
 delay(100);
  
if (distance <= stopdistance ){
  stopalarm();
}
else if (distance <= slowdistance){
  slowdownstate();
}

else{
   normalstate();
 }
  
  // TODO: position cursor at start of row 1
    lcd.setCursor(0, 0);
    // TODO: Display temp in Fahrenheit
    // format - Temp: xx.x F
    lcd.print("Distance: ");
    lcd.print(distance, 1);
    lcd.print(" ");
    delay(100);
}

void stopalarm() {
  lcd.setCursor(0, 1);
  lcd.print("STOP");
  delay(100);
  tone(buzzerPin, 4000);
  delay(50);
  noTone(buzzerPin);
  delay(50);
  lcd.clear();
    
}

  void normalstate() {
    lcd.setCursor(0, 1);
    lcd.print("Safe");
    delay(100);
    lcd.clear();
  
}

void slowdownstate() {
  lcd.setCursor(0, 1);
  lcd.print("SLOW DOWN");
  delay(100);
  tone(buzzerPin, 400);
  delay(200);
  noTone(buzzerPin);
  delay(100);
  lcd.clear();
  
}