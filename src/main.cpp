/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// leftRear             motor         11              
// leftMiddle           motor         1               
// leftFront            motor         2               
// rightRear            motor         20              
// rightMiddle          motor         10              
// rightFront           motor         9               
// leftIntake           motor         5               
// rightIntake          motor         6               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <iostream>
using namespace vex;

void stopDrivetrain();
void setVelocityIntake(int);
void setVelocityMotors(int, char);

// A global instance of competition
competition Competition;
int deadzone = 5;
// These are the thumbstick values.
double controllerLeftXPos;
double controllerLeftYPos;
double controllerRightXPos;
double controllerRightYPos;
bool controllerR1Bumper;
bool controllerR2Bumper;
double leftSpeed;
double rightSpeed;



// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    controllerLeftYPos = Controller1.Axis3.position(percent);
    controllerRightXPos = Controller1.Axis1.position(percent);
    leftSpeed = controllerLeftYPos + controllerRightXPos;
    rightSpeed = controllerLeftYPos - controllerRightXPos;
    controllerR1Bumper = Controller1.ButtonR1.pressing();
    controllerR2Bumper = Controller1.ButtonR2.pressing();
    leftFront.setVelocity(leftSpeed,percent);
    leftMiddle.setVelocity(leftSpeed,percent);
    leftRear.setVelocity(leftSpeed,percent);
    rightFront.setVelocity(rightSpeed,percent);
    rightMiddle.setVelocity(rightSpeed,percent);
    rightRear.setVelocity(rightSpeed,percent);

    

    // Drivetrain Code
    if(fabs(controllerLeftYPos) > deadzone || fabs(controllerRightXPos) > deadzone)
    {
      if(controllerLeftYPos > deadzone)
      {
        leftFront.spin(forward);
        leftMiddle.spin(forward);
        leftRear.spin(forward);
        rightFront.spin(forward);
        rightMiddle.spin(forward);
        rightRear.spin(forward);
      }
      if(controllerLeftYPos < deadzone)
      {
        leftFront.spin(reverse);
        leftMiddle.spin(reverse);
        leftRear.spin(reverse);
        rightFront.spin(reverse);
        rightMiddle.spin(reverse);
        rightRear.spin(reverse);      
      }
      if(controllerRightXPos > deadzone)
      {
        leftFront.spin(forward);
        leftMiddle.spin(forward);
        leftRear.spin(forward);
        rightFront.spin(forward);
        rightMiddle.spin(forward);
        rightRear.spin(forward);
      }
      if(controllerRightXPos < deadzone)
      {
        leftFront.spin(forward);
        leftMiddle.spin(forward);
        leftRear.spin(forward);
        rightFront.spin(forward);
        rightMiddle.spin(forward);
        rightRear.spin(forward);
      }
    }
    else
    {
      stopDrivetrain();
    }

    std::cout << leftFront.velocity(percent) << std::endl;
    // Intake Code
    if(controllerR1Bumper == true)
    {
      leftIntake.spin(forward);
      rightIntake.spin(forward);
    }
    else if (controllerR2Bumper == true)
    {
      rightIntake.spin(reverse);
      leftIntake.spin(reverse);
    }
    else
    {
      rightIntake.stop();
      leftIntake.stop();
    }



    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}

void stopDrivetrain()
{
  leftRear.stop();
  leftMiddle.stop();
  leftFront.stop();
  rightRear.stop();
  rightMiddle.stop();
  rightFront.stop();
}
// void setVelocity(int velocity, char side)
// {
//   if(side == 'R')
//   {
//     rightRear.setVelocity(velocity,percent);
//     rightMiddle.setVelocity(velocity,percent);
//     rightFront.setVelocity(velocity,percent);
//   }
//   if(side == 'L')
//   {
//     leftRear.setVelocity(velocity,percent);
//     leftMiddle.setVelocity(velocity,percent);
//     leftFront.setVelocity(velocity,percent);
//   }  
//}
void setVelocityIntake(int velocity)
{
  leftIntake.setVelocity(velocity,percent);
  rightIntake.setVelocity(velocity,percent);
}

