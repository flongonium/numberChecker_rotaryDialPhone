/*
 * buttonsIndoor.h
 *
 *  This file contains functions to bypass the dial and to automate the locking process.
 */

#ifndef BUTTONSINDOOR_H_
#define BUTTONSINDOOR_H_

// hardware input
int inputDoor       = 9;
int inputDoorButton = 8;

int manualStateOld;


/*-------------------------------- SETUP ---------------------------------*/
void doorSetup()
{
  pinMode(inputDoor,        INPUT_PULLUP);
  pinMode(inputDoorButton,  INPUT_PULLUP);
}


/*-------------------------------- MANUAL OPEN ----------------------------*/
void openAndCloseManual()
{
  int manualState = digitalRead(inputDoorButton);
  if (manualState != manualStateOld)
  {
    switch (manualState)
    {
      case LOW:
      motorIn();
      delay(4950);
      motorHold();
      delay(5000);  //give enough time to open door, before it closes again
      break;

      case HIGH:
      motorOut();
      delay(4950);
      motorHold();
      delay(50);
      break;
    }
  manualStateOld = manualState;
  }
}




#endif /* BUTTONSINDOOR_H_ */
