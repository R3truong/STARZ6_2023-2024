// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    20, 18, 19, 17, 5
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "vex.h"
#include <iostream>

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
// Movement Motor Variable Declarations
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
bool resetIntakePosition;

// driver control function Declarations
void setMotorVelocities(float left, float right);
void spinMotors();
void stopMotors();
void spinIntake();
void stopIntake();
int openIntake();
void closeIntake();
void reverseAuto();
void autoDriveForward(float left, float right, int mili);

// Autonomous Variable Declarations
bool resetOrientation;


// autonomous function declarations
void spinMotorsForwardAuton();
void spinMotorsReverseAuton();
void driveToGoal(float left, float right, int mili);
void drivePID();
void loadCatapaultAuton();

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
  catapaultConstraint.resetPosition();
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

void autonomous(void) 
{
  // leftCatapault.setVelocity(25,percent);
  // rightCatapault.setVelocity(25,percent);
  // loadCatapaultAuton();
  // spinMotors();
  // openIntake();
  // wait(0.5,msec);
  // stopMotors();
  // closeIntake();
  // spinIntake();
// Movement
  leftCatapault.setVelocity(20,percent);
  rightCatapault.setVelocity(20,percent);
  leftCatapault.spin(forward);
  rightCatapault.spin(forward);
  wait(1000,msec);
  leftCatapault.stop();
  rightCatapault.stop();
  leftCatapault.setStopping(hold);
  rightCatapault.setStopping(hold);

  driveToGoal( 100, 100, 264);
  wait(264,msec);

  driveToGoal( 100, -80, 320);
 // driveToGoal( -80, 100, 290);
//  wait(264,msec);
  //forward
  autoDriveForward(70, 70, 200);
  wait(264,msec);
  autoDriveForward( 70, 70, 3000);
  wait(1000,msec);

 // driveToGoal(100,-20,380);
 // driveToGoal(100,100,1000);

 // driveToGoal( -100, 100, 10);
  stopMotors();
  

 // openIntake();
 // spinIntake();
 // thread rearLeft([]
 // {
 //   spinMotors();
 // });
 // closeIntake();

  
}
                                      // PID CODE

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
    std::cout << catapaultConstraint.position(degrees) << std::endl;
    // Controller Variables
    deadzone = 9;
    controllerYAxis = Controller1.Axis3.position(percent); // Left Stick
    controllerXAxis = Controller1.Axis1.position(percent); // Right Stick

    // Intake and Shooter Variables
    clawButton = Controller1.ButtonL2.pressing();  // L2
    intakeButton = Controller1.ButtonL1.pressing(); // R2
    loadCatapault = Controller1.ButtonR1.pressing(); // R1
    fireCatapault = Controller1.ButtonR2.pressing(); // L1
    resetIntakePosition = Controller1.ButtonDown.pressing(); // down arrow on dpad
    
    // Velocities of said variables
    leftVelocity = controllerYAxis + controllerXAxis;
    rightVelocity = controllerYAxis - controllerXAxis;
    setMotorVelocities(leftVelocity, rightVelocity);
    rightCatapault.setVelocity(25,percent);
    leftCatapault.setVelocity(25,percent);
    // Try velocity of 40 for catapault

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
    // if(intakeButton)
    // {
    //   spinIntake();
    // }
    // else
    // {
    //   stopIntake();
    // }
    if(clawButton && intakeOpen.position(degrees) < 190)
    {
      thread rearRight([]
      {
        openIntake();
      });    }
    if(resetIntakePosition)
    {
      intakeOpen.resetPosition();
    }

    // Shooter Code
   
    if(loadCatapault && fabs(catapaultConstraint.position(degrees)) < 76)
    {
      leftCatapault.spin(forward);
      rightCatapault.spin(forward);
    }
    else if(fabs(catapaultConstraint.position(degrees)) > 76 && !fireCatapault)
    {  
      // std::cout << "test" << std::endl;   
      leftCatapault.stop();
      rightCatapault.stop();
      leftCatapault.setStopping(hold);
      rightCatapault.setStopping(hold);
    }
    else if(fireCatapault)
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

}

void spinMotors()
{
  Drivetrain.drive(forward);
}
void spinMotorsForwardToAuton()
{
 
}
void spinMotorsReverseAuton()
{
  // thread rearLeft([]
  // {
  //   RearLeft.spin(reverse);
  // });
  
}

void stopMotors()
{
  Drivetrain.stop();
}
int openIntake()
{
  intakeOpen.spinToPosition(-135, degrees);
  leftIntake.setVelocity(100,percent);
  rightIntake.setVelocity(100,percent);
  leftIntake.spin(forward);
  rightIntake.spin(forward);
  wait(500,msec);
  intakeOpen.stop();
  wait(1000,msec);
  stopIntake();

  return 0;
}
void closeIntake()
{
}
void spinIntake()
{

}
void stopIntake()
{
  leftIntake.stop();
  rightIntake.stop();
}
void Leftturn()
{
 
}


// Autonomous Functions
void driveToGoal(float left, float right,int mili)
{
  
}

void loadCatapaultAuton()
{
  // leftCatapault.spinFor(forward,360,degrees);
  // rightCatapault.spinFor(forward,360,degrees);
  reverseAuto();
  stopMotors();
}
void autoDriveForward(float left, float right,int mili)
{
  setMotorVelocities(left, right);
  spinMotors();
  wait( mili ,msec);
  stopMotors();
}
void reverseAuto()
{
  
}