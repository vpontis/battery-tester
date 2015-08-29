/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground

 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

#include <SD.h>
#include <SPI.h>

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int chipSelect = 4;

int sensorValue = 0;        // value read from the pot
long startTime;
long currTime;
String dataString;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  startTime = millis();

  // Initialize SD card
  Serial.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

// Voltage Values
// 830 ~ 3.69
// 826 ~ 3.68
// 825 ~ 3.67
// 821 ~ 3.66
// 814 ~ 3.62
// 809 ~ 3.60
// 805 ~ 3.58
// 798 ~ 3.55
// 789 ~ 3.50

// Resistor
// 11.2 Ohms

// USB Delivers 4.55 V to Arduino

void loop() {
  // read the analog in value:
  dataString = "";
  sensorValue = analogRead(analogInPin);
  currTime = (millis() - startTime)/1000;

  // print the results to the serial monitor:
  dataString += "sensor = ";
  dataString += sensorValue;
  dataString += ", time = ";
  dataString += currTime;

  Serial.println(dataString);

  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
  } else {
    Serial.println("error opening datalog.txt");
  }

  // wait 5 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(500);
}
