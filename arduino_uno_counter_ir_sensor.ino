#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
//#include <TinyWireM.h> // Enable this line if using Adafruit Trinket, Gemma, etc.

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment(); //end Adafruit requirements

const int sensorPin = 0; //analog pin 0
const int ledPin = 13;  // the pin that the LED is attached to

// vars
int sensorCounter = 0;   // counter for the number of button presses
int sensorState = 0;     // current state of the sensor

void setup() {
  // initialize the sensor pin and input
  pinMode(sensorPin, INPUT);
  // initialize the LED as an output
  pinMode(ledPin, OUTPUT);
  // initialize serial communication
  Serial.begin(9600);
  
// set the matrix 
    matrix.begin(0x70);
  }


void loop() {
  // read the sensor input pin:
  sensorState = analogRead(sensorPin);

  // if sensor is closer than than x distance
  if (sensorState > 460 ) {
    
    sensorCounter++;
    Serial.println(sensorState);
    Serial.print("number of counts:  ");
    Serial.println(sensorCounter);
   
    // show output on the digital display
    matrix.print(sensorCounter);
    matrix.writeDisplay();
    
    // slow down the output
    delay(500);
  } 

  
  // turns on the LED every ten counts 
  if (sensorCounter % 10 == 0) {
    digitalWrite(ledPin, HIGH);
  } else {
   digitalWrite(ledPin, LOW);
  }
  
}
