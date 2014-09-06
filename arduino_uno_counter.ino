/*************************************************** 
based off these two tutorials:

http://arduino.cc/en/Tutorial/ButtonStateChange
https://learn.adafruit.com/adafruit-led-backpack/0-dot-56-seven-segment-backpack

and these libraries:

https://github.com/adafruit/Adafruit-GFX-Library
https://github.com/adafruit/Adafruit-LED-Backpack-Library
 
 ****************************************************/

#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
//#include <TinyWireM.h> // Enable this line if using Adafruit Trinket, Gemma, etc.

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();

//end Adafruit

// this constant won't change:
const int  buttonPin = 2;    // the pin that the pushbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
  
// set the matrix 
    matrix.begin(0x70);
  }


void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes:  ");
      Serial.println(buttonPushCounter);
       
      // show output on the digital display
      matrix.print(buttonPushCounter);
      matrix.writeDisplay();
    } 
    else {
      // if the current state is LOW then the button
      // wend from on to off:
      Serial.println("off"); 
      
      //write somthing to the digital display
      matrix.print(0xFF, HEX); // button off, this won't display the zero so did the below
      matrix.writeDigitNum(1, 0, 0);// (digit from left, display, dot bolean)
      matrix.writeDisplay();
    }
  }
  // save the current state as the last state, 
  //for next time through the loop
  lastButtonState = buttonState;
  
  // turns on the LED every four button pushes by 
  // checking the modulo of the button push counter.
  // the modulo function gives you the remainder of 
  // the division of two numbers:
  if (buttonPushCounter % 4 == 0) {
    digitalWrite(ledPin, HIGH);
  } else {
   digitalWrite(ledPin, LOW);
  }
  
}
