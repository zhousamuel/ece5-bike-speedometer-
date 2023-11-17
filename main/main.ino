#include <LiquidCrystal.h>

int led = 13; //LED Pin
int sensor = 10; //sensor pin
int val; //numeric variable
float hall_thresh = 100.0;
int counter = 0; //count how many times magnet
int Contrast = 75;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  analogWrite(6, Contrast); // set contrast to pin 6

  pinMode(led, OUTPUT); //set led as output
  pinMode(sensor, INPUT); //set sensor pin as input
  lcd.begin(16, 2); //set up the LCD's number of columns and rows
  lcd.print("BIKE SPEEDOMETER"); // print BIKE SPEEDOMETER on LCD
}

void loop() {
  lcd.setCursor(0, 1);
  val = digitalRead(sensor);
  if(val == LOW)
  {
    counter += 1;
  }
  lcd.print("Counter: ");
  lcd.print(counter);

  delay(100);
}
