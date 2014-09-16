/*************************************************** 
based off these two tutorials:

http://playground.arduino.cc/Code/PIRsense

https://learn.adafruit.com/adafruit-led-backpack/0-dot-56-seven-segment-backpack

and these libraries for the display:

https://github.com/adafruit/Adafruit-GFX-Library
https://github.com/adafruit/Adafruit-LED-Backpack-Library
 
 ****************************************************/

#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
//#include <TinyWireM.h> // Enable this line if using Adafruit Trinket, Gemma, etc.

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();

//end Adafruit

//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 30;        

//the time when the sensor outputs a low impulse
long unsigned int lowIn;         

//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped
long unsigned int pause = 1000;  

boolean lockLow = true;
boolean takeLowTime;  

// this constant won't change:
const int  pirPin = 3;    // the pin that the pushbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int pirPushCounter = 0;   // counter for the number of PIR changes
int pirState = 0;         // current state of the PIR
int lastPirState = 0;     // previous state of the PIR

void setup() {
  // initialize the PIR pin as a input:
  pinMode(pirPin, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
  digitalWrite(pirPin, LOW);
  
  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(10);
  
// set the matrix 
    matrix.begin(0x70);
  }


void loop() {
  // read the PIR input pin:
  pirState = digitalRead(pirPin);
  
   if(digitalRead(pirPin) == HIGH){
       digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
       if(lockLow){  
         //makes sure we wait for a transition to LOW before any further output is made:
         lockLow = false;            
         Serial.println("---");
         Serial.print("motion detected at ");
         Serial.print(millis()/1000);
         Serial.println(" sec"); 
         delay(10);
         
         pirPushCounter++;
         Serial.println("on");
         Serial.print("number of counts:  ");
         Serial.println(pirPushCounter);
         
         // show output on the digital display
         matrix.print(pirPushCounter);
         matrix.writeDisplay();
         }         
         takeLowTime = true;
         
         
       }
       
    if(digitalRead(pirPin) == LOW){       
       digitalWrite(ledPin, LOW);  //the led visualizes the sensors output pin state

       if(takeLowTime){
        lowIn = millis();          //save the time of the transition from high to LOW
        takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }
       //if the sensor is low for more than the given pause, 
       //we assume that no more motion is going to happen
       if(!lockLow && millis() - lowIn > pause){  
           //makes sure this block of code is only executed again after 
           //a new motion sequence has been detected
           lockLow = true;                        
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(10);
           
           // if the current state is LOW then the button
           // wend from on to off:
           Serial.println("off"); 
          
           //write somthing to the digital display
           matrix.print(0xFF, HEX); // button off, this won't display the zero so did the below
           matrix.writeDigitNum(1, 0, 0);// (digit from left, display, dot bolean)
           matrix.writeDisplay();
           }
       }
  
}
