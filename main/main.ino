#include <LiquidCrystal.h>
const float pi = 3.14;   
int sensor = 13;  //sensor pin
float counter = 0; //count how many times magnet
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float bike_radius = 0.28; // meters
float bike_circum = 2 * pi * bike_radius; // meters
const float timeInterval = 3000; // update speed every 3 seconds

float distance = 0; // keeps track of total distance
int rotations = 0; // keeps track of total rotations

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT); //set sensor pin as input (13)
  lcd.begin(16, 2); //set up the LCD's number of columns and rows
}

void loop() {
  lcd.setCursor(0,0); // set position of speed on lcd
  lcd.print("Speed: ");

  float event_started = millis(); // start counting from here
  counter = 0; // keeps track of the total amount of passes each cycle

  int previous = LOW; // keeps track of state of the sensor

  while(millis() - event_started < timeInterval){

    int val = digitalRead(sensor);
    if(val != previous)
    {
      counter += 1;
      previous = val;
    }
  }

  counter /= 2; // state changes 2 times each revolution, so we must divide by 2

  // speed -> (circumference * rpm) / time (milliseconds)
  // m * (counter * 12 rpm) / (time * 1000)
  // circumference : meters
  // counter : reveloutions per second
  // timeInterval = seconds

  // float speed = (circumference * (counter / 5)) / (timeInterval / 1000); 
  float meters_per_3_seconds = counter * bike_circum;
  float speed = (meters_per_3_seconds * 3600) / (1609.34 * 3);
  //lcd.print(counter);
  lcd.print(speed);
  lcd.print(" mph");
  //Serial.println(counter);

  rotations += counter;

   lcd.setCursor(0, 1);
  // print distance as meters and speed as miles per hour
   distance = (rotations) * (2*pi*bike_radius);
   lcd.print("Distance: ");
   lcd.print(rotations);
   lcd.print(" m");
}