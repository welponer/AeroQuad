/*
  AeroQuad v3.0 - April 2011
  www.AeroQuad.com 
  Copyright (c) 2011 Ted Carancho.  All rights reserved.
  An Open Source Arduino based multicopter.
 
  This program is free software: you can redistribute it and/or modify 
  it under the terms of the GNU General Public License as published by 
  the Free Software Foundation, either version 3 of the License, or 
  (at your option) any later version. 

  This program is distributed in the hope that it will be useful, 
  but WITHOUT ANY WARRANTY; without even the implied warranty of 
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
  GNU General Public License for more details. 

  You should have received a copy of the GNU General Public License 
  along with this program. If not, see <http://www.gnu.org/licenses/>. 
*/

#ifndef _AEROQUAD_MOTORS_MAPLER5_H_
#define _AEROQUAD_MOTORS_MAPLER5_H_

#include <WProgram.h>
#include "Motors.h"

#define MOTORPIN1 12
#define MOTORPIN2 11
#define MOTORPIN3 27
#define MOTORPIN4 28
#define MOTORPIN5 2
#define MOTORPIN6 3
#define MOTORPIN7 -1
#define MOTORPIN8 -1

void initializeMotors(byte numbers) {

}

void initializeMotors(NB_Motors numbers) {
  numberOfMotors = numbers;
    
  Timer3.setPrescaleFactor(72);
  Timer3.setOverflow(20000);
  
  pinMode(MOTORPIN1, PWM);
  pinMode(MOTORPIN2, PWM);
  pinMode(MOTORPIN3, PWM);
  pinMode(MOTORPIN4, PWM);

  if (numberOfMotors == SIX_Motors) {
    Timer2.setPrescaleFactor(72);
    Timer2.setOverflow(20000);
    
    pinMode(MOTORPIN5, PWM);
    pinMode(MOTORPIN6, PWM);
  }   

  commandAllMotors(1000);
}

void writeMotors() {
  Timer3.setCompare(TIMER_CH1, motorCommand[MOTOR1]);
  Timer3.setCompare(TIMER_CH2, motorCommand[MOTOR2]);
  Timer3.setCompare(TIMER_CH3, motorCommand[MOTOR3]);
  Timer3.setCompare(TIMER_CH4, motorCommand[MOTOR4]);
  
  if (numberOfMotors == SIX_Motors) {  
    Timer2.setCompare(TIMER_CH1, motorCommand[MOTOR5]);
    Timer2.setCompare(TIMER_CH2, motorCommand[MOTOR6]);
  }   
}
  
void commandMotor( byte motor, int command) {
  motorCommand[motor] = command;
  writeMotors();
}
  
void commandAllMotors(int command) {
  for( int i = 0; i < 8; i++)    // Todo: LASTMOTOR not know here
    motorCommand[i] = command;
  writeMotors();
}  






#endif


