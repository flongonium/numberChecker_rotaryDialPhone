/*
 * @todo move doorState stuff to buttonsIndoor.h
 */

#include "Arduino.h"
#include "readDial.h"
#include "linearMotor.h"
#include "buttonsIndoor.h"

int handsetHungUp     = HIGH;
int handsetPickedUp   = LOW;
int lastHandsetState  = 0;

bool checkPW          = false;

/* ------------------------------- SETUP ------------------------------------------------------*/
void setup()
{
  // motor
  motorSetup();

  // phone
  dialSetup();

  // door
  doorSetup();

  //Serial.begin(115200);
}

/* ------------------------------- MAIN PROGRAM -----------------------------------------------*/
void loop()
{

  int handsetState = digitalRead(inputHandset);

    // Check if handset is picked up and look for dial events
    if(handsetState==handsetPickedUp)
    {
      // Password is true
      if (checkPW == true)
      {
        motorIn();
        delay(4950);
        motorHold();
        passwordIsCorrect = false;
      }
      checkPW = readPrintDial();
    }
    // Check if Handset is hung up and decide if motor should start extending or not
    else if (handsetState==handsetHungUp)
    {
      int doorState = digitalRead(inputDoor);

      // Check if door is closed, then motor is able to extend. Otherwise, motor will hold its position
      if(doorState==HIGH)
      {
        if(motorState==0)
        {
          delay(500);  // To ensure, that door is all the way closed before motor movement
          motorOut();
          delay(4950);
          motorHold();
        }
      }
      else
      {
        motorHold();
      }

    }
      //check if you want to open the door manually (from the inside)
  openAndCloseManual();

}
