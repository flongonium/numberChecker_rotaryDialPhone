/*
 * readDial.h
 * Read dialed numbers from your phone, store them.
 * In this file you define the password for comparison (see .ino file)
 *
 * @todo restructure password section
 */

#ifndef READDIAL_H_
#define READDIAL_H_

// hardware input
int inputDial     = 13;
int inputHandset  = 12;

// dial
int needToPrint   = 0;
int count;

// incident checking
int           lastState                       = LOW;
int           trueState                       = LOW;
long          lastStateChangeTime             = 0;
int           cleared                         = 0;
unsigned int  dialHasFinishedRotatingAfterMs  = 400;
unsigned int  debounceDelay                   = 10;

// password
int           passwordLength                  = 4;
int           password                        = 0000; //YOUR PASSWORD HERE
int           insertedPassword[]              = {0, 0, 0, 0};
bool          passwordIsCorrect               = false;
int           attempt                         = passwordLength-passwordLength;


/*--------------------------- SETUP ---------------------------------------*/
void dialSetup()
{
  pinMode(inputDial,    INPUT_PULLUP);
  pinMode(inputHandset, INPUT_PULLUP);
}


/*--------------------------- MAIN PROGRAM ---------------------------------*/
bool readPrintDial()
{
  // read the value of the dial
  int readDial = digitalRead(inputDial);

  // the dial isn't being dialed, or has just finished being dialed.
  if ((millis() - lastStateChangeTime) > dialHasFinishedRotatingAfterMs)
  {
    if (needToPrint)
    {
      // if it's only just finished being dialed, we store the number in the variable
      // and reset the count. We mod the count by 10 because '0' will send 10 pulses.
      insertedPassword[attempt] = count % 10;
      needToPrint = 0;
      count = 0;
      cleared = 0;

      // the first 3 cases just increment the attempt.
      switch (attempt)
      {
        case 0:
        attempt++;
        break;

        case 1:
        attempt++;
        break;

        case 2:
        attempt++;
        break;

        // case 3 (the fourth time dial is dialed) checks if entered password is correct and resets inserted password either if PW was correct or not
        case 3:
        if (password == insertedPassword[0]*1000+insertedPassword[1]*100+insertedPassword[2]*10+insertedPassword[3])
        {
          insertedPassword[0] = 0;
          insertedPassword[1] = 0;
          insertedPassword[2] = 0;
          insertedPassword[3] = 0;
          attempt = 0;
          passwordIsCorrect = true;
          break;
        }
        else
        {
          insertedPassword[0] = 0;
          insertedPassword[1] = 0;
          insertedPassword[2] = 0;
          insertedPassword[3] = 0;
          attempt = 0;
          break;
        }
      }
    }
  }

  if (readDial != lastState)
  {
    lastStateChangeTime = millis();
  }

  // debounce - this happens once it's stablized
  if ((millis() - lastStateChangeTime) > debounceDelay)
  {
    // Check if the switch has either just gone from closed->open or vice versa.
    if (readDial != trueState)
    {
      trueState = readDial;
      if (trueState == HIGH)
      {
        // increment the count of pulses if it's gone high.
        count++;
        needToPrint = 1;
      }
    }
  }
  lastState = readDial;
  return passwordIsCorrect;
}





#endif /* READDIAL_H_ */
