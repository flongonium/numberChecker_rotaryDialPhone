/*
 * linearMotor.h
 *
 * This file contains the functions to steer a linear motor.
 */

#ifndef LINEARMOTOR_H_
#define LINEARMOTOR_H_

// hardware input
int relayOutput_1  = 7;
int relayOutput_2  = 6;

// variable
int motorState     = 0;


/*-------------------------------- SETUP ------------------------------------*/
// define pins as outputs to send signals to relays
void motorSetup()
{
  pinMode(relayOutput_1, OUTPUT);
  pinMode(relayOutput_2, OUTPUT);
}

/*-------------------------------- HOLD -------------------------------------*/
// cut power source from motor by setting both relays low
void motorHold()
{
  digitalWrite(relayOutput_1,LOW);
  digitalWrite(relayOutput_2,LOW);
  delay(50);
}

/*-------------------------------- MOTOR IN ---------------------------------*/
// Motor retracts
void motorIn()
{
  digitalWrite(relayOutput_1,LOW);
  digitalWrite(relayOutput_2,HIGH);
  delay(50);
  motorState = 0;
  //Serial.println("Motorstate: ");
  //Serial.println(motorState);
}


/*-------------------------------- MOTOR OUT ---------------------------------*/
void motorOut()
{
  digitalWrite(relayOutput_1,HIGH);
  digitalWrite(relayOutput_2,LOW);
  delay(50);
  motorState = 1;
  //Serial.println("Motorstate: ");
  //Serial.println(motorState);
}




#endif /* LINEARMOTOR_H_ */
