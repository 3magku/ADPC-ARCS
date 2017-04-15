// Include Libraries
#include "Arduino.h"
#include "SFE_BMP180.h"
#include "PiezoSpeaker.h"

// Pin Definitions
#define PIEZOSPEAKER_PIN_SIG  5

// Global variables and defines
unsigned int piezoSpeakerWhoopeeLength          = 12; // amount of notes in melody
unsigned int piezoSpeakerWhoopeeMelody[]        = {NOTE_C7, NOTE_E7, NOTE_G7, NOTE_C7, NOTE_G7, NOTE_C8, NOTE_C7, NOTE_E7, NOTE_G7, NOTE_C7, NOTE_G7, NOTE_C8}; // list of notes. List length must match WhoopeeLength!
unsigned int piezoSpeakerWhoopeeNoteDurations[] = {800    , 800    , 800    , 400    , 800    , 400    , 800    , 800    , 800    , 400    , 800    , 400}; // note durations; 4 = quarter note, 8 = eighth note, etc. List length must match WhoopeeLength!

// Constructors
SFE_BMP180 bmp180;
PiezoSpeaker piezoSpeaker(PIEZOSPEAKER_PIN_SIG);

// define vars for pressure reading and trigger
#define PRESSURE_SENSITIVITY 5 // define pressure increment value to trigger sound (mb)
double previousBmp180Pressure = 10000;

/* This code sets up the essentials for your circuit to work. It runs first every time your circuit is powered with electricity. */
void setup() {
  // Setup Serial which is useful for debugging
  Serial.begin(9600);
  Serial.println("start");

  //Initialize I2C device
  bmp180.begin();
}

/* This code is the main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop. */
void loop() {
  // BMP180
  // Read pressure from barometric sensor
  double bmp180Pressure = bmp180.getPressure();
  Serial.print(F("Pressure: ")); Serial.print(bmp180Pressure, 1); Serial.print(F(" [hPa]"));
  Serial.print(F("\tprevious reading: ")); Serial.print(previousBmp180Pressure, 1); Serial.print(F(" [hPa]"));

  // Determine pressure change to previous reading
  double bmp180PressureChange = bmp180Pressure - previousBmp180Pressure;
  Serial.print(F("\tchange: ")); Serial.print(bmp180PressureChange, 1); Serial.println(F(" [hPa]"));
  previousBmp180Pressure = bmp180Pressure;

  // If pressure has been increased by more then PRESSURE_SENSITIVITY hPa ...
  if ( bmp180PressureChange >= PRESSURE_SENSITIVITY ) {
    Serial.println(F(">>>>> Whoopee!!!"));
    // The PiezoSpeaker will play the Whoopee tune
    piezoSpeaker.playMelody(piezoSpeakerWhoopeeLength, piezoSpeakerWhoopeeMelody, piezoSpeakerWhoopeeNoteDurations);
  }

  delay(500);
}

/*******************************************************

     Circuito.io is an automatic generator of schematics and code for off
     the shelf hardware combinations.

     Copyright (C) 2016 Roboplan Technologies Ltd.

     This program is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program.  If not, see <http://www.gnu.org/licenses/>.

     In addition, and without limitation, to the disclaimers of warranties
     stated above and in the GNU General Public License version 3 (or any
     later version), Roboplan Technologies Ltd. ("Roboplan") offers this
     program subject to the following warranty disclaimers and by using
     this program you acknowledge and agree to the following:
     THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND
     WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN
     HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT
     NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS
     FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY
     STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE.
     YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
     ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT
     SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES
     NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO
     SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE
     FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT
     VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
     RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN.
     YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN,
     ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF
     THE ABOVE.
********************************************************/
