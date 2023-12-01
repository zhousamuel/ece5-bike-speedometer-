#include <LiquidCrystal.h>
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

// ISR(TIMER1_COMPA_vect)
// {
// count++;
// flash();
// }

void setup() {

  Serial.begin(9600);
  // analogWrite(6, Contrast);  // set contrast to pin 6

  // pinMode(led, OUTPUT);    
  pinMode(sensor, INPUT);         //set sensor pin as input (13)
  lcd.begin(16, 2);        //set up the LCD's number of columns and rows

  // cli();
  // TCCR1A = 0;
  // TCCR1B = 0; 
  // OCR1A = reload;
  // TCCR1B = (1<<WGM12) | (1<<CS12); 
  // TIMSK1 = (1<<OCIE1A); 
  // sei(); 
}

void loop() {
  lcd.setCursor(0,0);
  //lcd.print("Speed: ");
  lcd.print("Speed: ");

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

  //meters * rev/5s * 1 mile/1609.344 meters * 5 * 60s/1min * 60min/1hr  
  //miles/5 seconds 
  //1609.344

  // float speed = (circumference * (counter / 5)) / (timeInterval / 1000); <- 
  float speed =  (counter * 12 * (0.56 * pi)) / 1609.344;
  //lcd.print(counter);
  lcd.print(speed);
  lcd.print(" mph");
  //Serial.println(counter);

  rotations += counter;

   lcd.setCursor(0, 1);
  // bike_radius => m
  distance = (rotations) * (2*pi*bike_radius);
   lcd.print("Distance: ");
   lcd.print(rotations);
   lcd.print("m");
}