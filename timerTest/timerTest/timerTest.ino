#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>
#include <TimerOne.h>
const float pi = 3.14;   
// int led = 13 // LED Pin
int sensor = 13;  //sensor pin
int counter; //count how many times magnet
//int Contrast = 75
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float bike_radius = 0.28; //m
const float timeInterval = 5000; // update speed every 5 seconds

float distance = 0;
int rotations = 0;

void setup() {

  Serial.begin(9600);
  Timer1.initialize(5000); // set to 5 seconds
  Timer1.attachInterrupt(speedPrint)
  pinMode(sensor, INPUT);         //set sensor pin as input (13)
  lcd.begin(16, 2);        //set up the LCD's number of columns and rows

  lcd.setCursor(0,0)
  lcd.print("Speed:")
  lcd.setCursor(0,1)
  lcd.print("Distance: ")
}

void loop() {

  int val = digitalRead(sensor);
  if(val != previous)
  {
    counter += 1;
    previous = val;
  }

  rotations += counter;
}

void speedPrint(){
  lcd.setCursor(0,0);
  lcd.print("Speed: ");
  counter /= 2; // NEEDED FOR CALCULATIONS
  float speed =  (counter * 12 * (0.56 * pi)) / 1609.344;
  lcd.print(speed);
  lcd.print(" mph");

  lcd.setCursor(0, 1);
  // bike_radius => m
   distance = (rotations) * (2*pi*bike_radius);
   lcd.print("Distance: ");
   lcd.print(rotations);
   lcd.print("m");


  counter = 0;
}