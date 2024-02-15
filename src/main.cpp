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
// RearRight            motor         20              
// RearLeft             motor         11              
// CenterRight          motor         19              
// CenterLeft           motor         12              
// FrontRight           motor         10              
// FrontLeft            motor         1               
// InertiaSensor        inertial      5               
// rightIntake          motor         6               
// leftIntake           motor         13              
// rightClawSpin        motor         9               
// leftClawSpin         motor         18              
// leftCatapault        motor         4               
// rightCatapault       motor         3               
// catapaultSwitch      limit         A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <iostream>

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
// Movement Motor Variable Declarations
float frontLeft;
float frontRight;
float centerLeft;
float centerRight;
float rearLeft;
float rearRight;
float leftVelocity;
float rightVelocity;
int deadzone;
float controllerYAxis;
float controllerXAxis;


// Intake and Shooter Variable Declarations
bool intakeButton;
bool clawButton;
bool loadCatapault;
bool fireCatapault;

// driver control function Declarations
void setMotorVelocities(float left, float right);
void spinMotors();
void stopMotors();
void spinIntake();
void stopIntake();
void spinClawOut();
void stopClawSpin();

// Autonomous Variable Declarations
bool resetOrientation;

double KP = 0.0;
double KI = 0.0;
double KD = 0.0;  

double TURNKP = 0.0;
double TURNKI = 0.0;
double TURNKD = 0.0;  

int error; // SensorValue - desiredValue : positional value (deltaX)
int prevError = 0; // Position 20 miliseconds ago
int derivative; // error - prevError : speed
int totalError = 0; // total error = totalError += error

int turnError; // SensorValue - desiredValue : positional value (deltaX)
int turnPrevError = 0; // Position 20 miliseconds ago
int turnDerivative; // error - prevError : speed
int turnTotalError = 0; // total error = totalError += error

// autonomous function declarations
void driveToGoal();
void drivePID();

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
  InertiaSensor.calibrate();

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
                                      // PID CODE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// bool enablePID = true;
// double desiredPosition = 200;
// double desiredTurning = 0;
// Auton Functions
// void drivePID()
// {
//   while(enablePID)
//   {
//     // Lateral PID
//     double leftMotorPosition = CenterLeft.position(degrees);
//     double rightMotorPosition = CenterRight.position(degrees);
//     // average of two variables
//     double averagePosition = (leftMotorPosition + rightMotorPosition) / 2;

//     // Potential
//     error = averagePosition - desiredPosition; 
//     // Derivative
//     derivative = error - prevError;

//     // Velocity -> position -> Absement
//     // totalError += error;

//     double lateralMotorPower = (error * KP + derivative * KD);


//     // Turning PID
    

//     double turnDifference = (leftMotorPosition - rightMotorPosition) / 2;
//     turnError = turnDifference - desiredPosition; 
//     turnDerivative = turnError - turnPrevError;

//     // turnTotalError += turnError;

//     double turnMotorPower = (turnError * TURNKP + turnDerivative * TURNKD);

//     ////////////////////////////////////////////////////////////////////////////////
//     CenterLeft.spinFor(forward, lateralMotorPower + turnMotorPower,degrees);

//     prevError = error;
//     turnPrevError = turnError;
//     task::sleep(20);

//   }
// }
////////////////////////////////////////////////////////////////////////////////////////////////////////


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
  leftIntake.setVelocity(100,percent);
  rightIntake.setVelocity(100,percent);
  // User control code here, inside the loop
  while (1) {
    // Controller Variables
    deadzone = 5;
    controllerYAxis = Controller1.Axis3.position(percent); // Left Stick
    controllerXAxis = Controller1.Axis1.position(percent); // Right Stick

    // Intake and Shooter Variables
    clawButton = Controller1.ButtonL2.pressing();  // L2
    intakeButton = Controller1.ButtonR2.pressing(); // R2
    loadCatapault = Controller1.ButtonR1.pressing(); // R1
    fireCatapault = Controller1.ButtonL1.pressing(); // L1
    
    // Velocities of said variables
    leftVelocity = controllerYAxis + controllerXAxis;
    rightVelocity = controllerYAxis - controllerXAxis;
    setMotorVelocities(leftVelocity, rightVelocity);
    rightCatapault.setVelocity(40,percent);
    leftCatapault.setVelocity(40,percent);

    // Movement Code
    if(fabs(controllerYAxis) > deadzone || fabs(controllerXAxis) > deadzone)
    {
      spinMotors();
    }
    else
    {
      stopMotors();
    }
    
    // Intake Code
    if(intakeButton)
    {
      spinIntake();
    }
    else
    {
      stopIntake();
    }
    if(clawButton)
    {
      spinClawOut();
    }
    else if(!clawButton)
    {
      stopClawSpin();
    }

    // Shooter Code
    if(catapaultSwitch.pressing())
    {
      leftCatapault.setStopping(hold);
      rightCatapault.setStopping(hold);
      leftCatapault.stop();
      rightCatapault.stop();
    }
    else if(loadCatapault && !catapaultSwitch.pressing())
    {
      leftCatapault.spin(forward);
      rightCatapault.spin(forward);
    }
    if(fireCatapault && catapaultSwitch.pressing())
    {
      leftCatapault.setStopping(coast);
      rightCatapault.setStopping(coast);
      rightCatapault.spin(forward);
      leftCatapault.spin(forward);
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

void setMotorVelocities(float leftValue, float rightValue)
{
  RearLeft.setVelocity(leftValue, percent);
  RearRight.setVelocity(rightValue, percent);
  CenterLeft.setVelocity(leftValue, percent);
  CenterRight.setVelocity(rightValue, percent);
  FrontLeft.setVelocity(leftValue, percent);
  FrontRight.setVelocity(rightValue, percent);
}

void spinMotors()
{
  RearLeft.spin(forward);
  RearRight.spin(forward);
  CenterLeft.spin(forward);
  CenterRight.spin(forward);
  FrontLeft.spin(forward);
  FrontRight.spin(forward);
}

void stopMotors()
{
  RearLeft.stop();
  RearRight.stop();
  CenterLeft.stop();
  CenterRight.stop();
  FrontLeft.stop();
  FrontRight.stop();
}
void spinClawOut()
{
  thread leftClawThread([] {
    leftClawSpin.spinToPosition(-184, degrees);
  });
  thread rightClawThread([] {
    rightClawSpin.spinToPosition(184, degrees);
  });
}
void stopClawSpin()
{
  leftClawSpin.stop();
  rightClawSpin.stop();
  leftClawSpin.resetPosition();
  rightClawSpin.resetPosition();

}
void spinIntake()
{
  leftIntake.spin(reverse);
  rightIntake.spin(forward);
}
void stopIntake()
{
  leftIntake.stop();
  rightIntake.stop();
}


// Autonomous Functions
void driveToGoal()
{
  
}