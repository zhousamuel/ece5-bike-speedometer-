#include <LiquidCrystal.h>
const float pi = 3.14;   
// int led = 13 // LED Pin
int sensor = 13;  //sensor pin
int counter; //count how many times magnet
//int Contrast = 75
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float bike_radius = 0.13; //m
float circumference = 0.26 * pi;  // meters
const float timeInterval = 5000; // update speed every 5 seconds

float distance = 0;

// Variables for the bike turn lights
bool rightTurn = false;


void setup() {

  Serial.begin(9600);
  // analogWrite(6, Contrast);  // set contrast to pin 6

  // pinMode(led, OUTPUT);    
  pinMode(sensor, INPUT);         //set sensor pin as input (13)
  lcd.begin(16, 2);        //set up the LCD's number of columns and rows
}

void loop() {

  lcd.setCursor(0,0);
  //lcd.print("Speed: ");
  lcd.print("Counter: ");

  float event_started = millis();
  counter = 0;

  int previous = LOW;

  while(millis() - event_started < 5000){

    //ADD CODE FOR THE TURN LIGHTS

    int val = digitalRead(sensor);
    if(val != previous)
    {
      counter += 1;
      previous = val;
    }
    //Serial.println(counter);
    //delay(50); //prevents large counter numbers
  }

  counter /= 2; // NEEDED FOR CALCULATIONS

  // speed -> (circumference * rpm) / time (milliseconds)
  // m * (counter * 12 rpm) / (time * 1000)
  // circumference : meters
  // counter : reveloutions per second
  // timeInterval = seconds

  //float speed = (circumference * (counter / 5)) / (timeInterval / 1000);
  lcd.print(counter);
  //Serial.println(counter);

  // lcd.setCursor(0, 1);
  // bike_radius => m
  // distance += (counter) * (2*pi*bike_radius);
  // lcd.print("Distance: ");
  // lcd.print(distance);

}