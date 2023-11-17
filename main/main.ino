#include <LiquidCrystal.h>

const float pi = 3.14;
int led = 13;     //LED Pin
int sensor = 10;  //sensor pin
int val;          //numeric variable
int counter = 0;  //count how many times magnet
//int Contrast = 75;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float bike_radius = 0.13; //m
float circumference = 0.26 * pi;  // meters
const float timeInterval = 5000; // update speed every 5 seconds

float distance = 0;

//TURN LIGHT CODE
const int RightSwitch = 6;
const int RightBlink = 7;
const int LeftSwitch = 8;
const int LeftBlink = 9;

long RightSwitchMillis = 0; //Time stamp for when the switch last went to 1(HIGH). Initially set at 0(LOW)
int RightSwitchVal = 0; //Monitors the value of the Right Blinker switch, whether 1 or 0 (HIGH or LOW). Initially set at 0(LOW)
int previousRightSwitchVal = 0; //Monitors the value of the Right Blinker switch from last time it was checked. Initally set at 0(LOW)
int RightBlinkState = LOW; //State of the Right Blinker Light. Initally set to LOW(Off)
long RightFlashMillis = 0; //Time stamp for when rapid flash last went to 1(LOW), initially set at O(LOW)
long RightPulseMillis = 0; //Time stamp for when the Right Blinker value i was last adjusted
int R = 0; //variable used to count up and down for the Right Blinker pulses.
int RightPulse = LOW; //variable used to determine Fade In or Fade Out. HIGH means i=225 and going down, LOW means i=0 and going up.

long LeftSwitchMillis = 0;
int LeftSwitchVal = 0;
int previousLeftSwitchVal = 0;
int LeftBlinkState = LOW;
long LeftFlashMillis = 0;
long LeftPulseMillis = 0;
int L = 0;
int LeftPulse = LOW;

long interval = 1000;

void setup() {

  // Serial.begin(9600);
  // analogWrite(6, Contrast);  // set contrast to pin 6

  // set up turn lights
  pinMode(RightBlink, OUTPUT); 
  pinMode(RightSwitch, INPUT); 
  pinMode(LeftBlink, OUTPUT); 
  pinMode(LeftSwitch, INPUT); 

  pinMode(led, OUTPUT);           //set led as output
  pinMode(sensor, INPUT);         //set sensor pin as input
  lcd.begin(16, 2);               //set up the LCD's number of columns and rows
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Speed: ");
  float event_started = millis();
  counter = 0;

  while(millis() - event_started < 5000){
    val = digitalRead(sensor);
    if(val == LOW)
    {
      counter += 1;
    }
    // delay(50);
    
  float currentMillis = millis();

    //Right Blinker Code/////////////////////////////////////////////////////////////////////////////////////////////////////////
  RightSwitchVal = digitalRead(RightSwitch); //read and store Right Blinker switch status
  
  if ((RightSwitchVal == HIGH) && (previousRightSwitchVal == LOW)) //compares current switch status to previous status
    {
     previousRightSwitchVal = RightSwitchVal; //sets the current status as the old status in preparation for the next check
     RightSwitchMillis = currentMillis; //sets a time stamp at the current time
    }

   if ((RightSwitchVal == HIGH) && (currentMillis - RightSwitchMillis > interval/2) && (RightPulse == LOW) && (currentMillis - RightPulseMillis > interval/10000)) //checks if the Right Blinker switch is pressed and how long it has been pressed for,
        {                                                                                                                                                        // if the Pulse was last set LOW, and if it is time for another step in brightness.
         RightPulseMillis = currentMillis; //Time stamp used to check how long since the brightness, i, was last changed
         R++; //Adds 1 to R value. The value of R dictates light brightness
         RightBlinkState = R; //Sets the light brightness to the value of i.
         analogWrite(RightBlink, RightBlinkState); //Sets the blinker brightness to the dictates level. Why I cannot go directly use (RightBlink, R), I do not know...
         }
 
   if (R == 255) //checks value of R
    {
     RightPulse = HIGH; //if R is maxed out at 255, the RightPulse goes HIGH. This lets R decrease.
    }
    
   if ((RightSwitchVal == HIGH) && (currentMillis - RightSwitchMillis > interval/2) && (RightPulse == HIGH) && (currentMillis - RightPulseMillis > interval/10000)) //checks if the Right Blinker switch is pressed and how long it has been pressed for,
        {                                                                                                                                                           // if the Pulse was last set HIGH, and if it is time for another step in brightness.
         RightPulseMillis = currentMillis; //if the Right Blinker switch is pressed on and has been on for more than half a second, set a time stamp for the fade in. 
         R--; //Subtracts 1 from R value
         RightBlinkState = R; //Sets the value of light brightness to the value of R
         analogWrite(RightBlink, RightBlinkState); //set the blinker brightness to the value of RightBlinkState
          }
          
   if ((R == 0) && (currentMillis - RightSwitchMillis > interval/2)) // Checks if R is at 0 so that the brightening cycle can repeate. Also checks if the initial rapid flash sequence is over.
    {
      RightPulse = LOW; //if the above conditions are met, reset RightPulse to LOW.
    }

    if((RightSwitchVal == HIGH) && (currentMillis - RightFlashMillis > interval/50) && (currentMillis - RightSwitchMillis < interval/2)) //if the Right Blink switch is HIGH but less than half a second has elapsed,                                                                                                                                 
         {                                                                                                                                 // this checks if the Right Blink switch is HIGH and more than one-fifteith
        RightFlashMillis = currentMillis; // saves current time                                                                             //of a second has elapsed since the last time previousMillis10 was reset.
         
         if (RightBlinkState == LOW)
            RightBlinkState = HIGH;
          else
            RightBlinkState = LOW; //if more than one-fiftieth of a second has elapsed since the time stamp was reset, reverse the state of the Right Blinker.
            
          digitalWrite(RightBlink, RightBlinkState); // set the Right Blinker with the state of the variable:
          }
          
    if (RightSwitchVal == LOW) //checks if the Blinker switch is still on or not. If it is off, the following occurs...
         {
           previousRightSwitchVal = RightSwitchVal; //makes sure the previousBrakeSwitch value is reset to off when the switch is in fact off.
           RightBlinkState = LOW; //resets the blinker
           digitalWrite(RightBlink, RightBlinkState); //Overall, if the Right Blinker switch is off, keep the Right Blinker off. 
           R = 0; //resets R in preparation for the next usage.
         }

     //Left Blinker Code. Identical to Right Blinker Code.//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  LeftSwitchVal = digitalRead(LeftSwitch);
  
  if ((LeftSwitchVal == HIGH) && (previousLeftSwitchVal == LOW))
    {
     previousLeftSwitchVal = LeftSwitchVal;
     LeftSwitchMillis = currentMillis;
    }

   if ((LeftSwitchVal == HIGH) && (currentMillis - LeftSwitchMillis > interval/2) && (LeftPulse == LOW) && (currentMillis - LeftPulseMillis > interval/10000))
        {
         LeftPulseMillis = currentMillis;
         L++; 
         LeftBlinkState = L;
         analogWrite(LeftBlink, LeftBlinkState);
         }

   if (L == 255)
    {
     LeftPulse = HIGH;
    }
    
   if ((LeftSwitchVal == HIGH) && (currentMillis - LeftSwitchMillis > interval/2) && (LeftPulse == HIGH) && (currentMillis - LeftPulseMillis > interval/10000)) 
        {
         LeftPulseMillis = currentMillis;
         L--;
         LeftBlinkState = L;
         analogWrite(LeftBlink, LeftBlinkState);
          }
          
   if ((L == 0) && (currentMillis - LeftSwitchMillis > interval/2))
    {
      LeftPulse = LOW;
    }


    if((LeftSwitchVal == HIGH) && (currentMillis - LeftFlashMillis > interval/50) && (currentMillis - LeftSwitchMillis < interval/2))                                                                                                                                 
         {
        LeftFlashMillis = currentMillis;
         
         if (LeftBlinkState == LOW)
            LeftBlinkState = HIGH;
          else
            LeftBlinkState = LOW;
            
          digitalWrite(LeftBlink, LeftBlinkState);
         }
          
    if (LeftSwitchVal == LOW)
         {
           previousLeftSwitchVal = LeftSwitchVal;
           LeftBlinkState = LOW;
           digitalWrite(LeftBlink, LeftBlinkState);
           L = 0;
         }

  }

  // speed -> (circumference * rpm) / time (milliseconds)
  // m * (counter * 12 rpm) / (time * 1000)
  // circumference : meters
  // counter : reveloutions per second
  // timeInterval = seconds
  float speed = (circumference * (counter / 5)) / (timeInterval / 1000);
  //lcd.print(counter);
  lcd.print(speed);

  lcd.setCursor(0, 1);
  // bike_radius => m
  distance += (counter) * (2*pi*bike_radius);
  lcd.print("Distance: ");
  lcd.print(distance);

}