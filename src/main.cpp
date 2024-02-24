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
bool resetCatapaultPosition;

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
void autonCatapaultFire();
void driveToGoal(float left, float right, int mili);
void drivePID();
int catapaultAuton();

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
  intakeOpen.setPosition(0, degrees);

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
 // thread rearRight([]
//  {
 //   catapaultAuton();
 // });  
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
  // leftCatapault.setVelocity(20,percent);
  // rightCatapault.setVelocity(20,percent);
  // leftCatapault.spin(forward);
  // rightCatapault.spin(forward);
  // wait(1000,msec);
  // leftCatapault.stop();
  // rightCatapault.stop();
  // leftCatapault.setStopping(hold);
  // rightCatapault.setStopping(hold);

  Drivetrain.setDriveVelocity(55, percent); //start at matchload bar
  Drivetrain.driveFor(reverse, 4.15, inches);
  Drivetrain.turnFor(40, degrees);
  Drivetrain.driveFor(reverse, 13, inches);
  Drivetrain.turnFor(-13, degrees); //full length field setup position
  Drivetrain.setDriveVelocity(85, percent); 

  Drivetrain.driveFor(reverse, 35, inches); //forward full lenth of field
  Drivetrain.turnFor(-2, degrees);
  Drivetrain.driveFor(reverse, 45, inches);
  Drivetrain.setDriveVelocity(55, percent); 
  Drivetrain.turnFor(-24.5, degrees); // turnRight 45 degree turns 
  Drivetrain.driveFor(reverse, 22, inches);
  Drivetrain.turnFor(-26, degrees); //oposite side turning towards goal

  Drivetrain.setDriveVelocity(70, percent);
  Drivetrain.driveFor(reverse, 9.5, inches);
  Drivetrain.driveFor(forward, 9.5, inches); //Back up back Ram code
  Drivetrain.driveFor(reverse, 9.5, inches);
  Drivetrain.driveFor(forward, 9.5, inches);

  Drivetrain.setDriveVelocity(60, percent);
  Drivetrain.turnFor(-49.5, degrees); //turn towards from of goal
  Drivetrain.driveFor(reverse, 14.5, inches); //]
  Drivetrain.turnFor(24.5, degrees);        //] movement around goal
  Drivetrain.driveFor(reverse, 35, inches); //]
  Drivetrain.turnFor(24.5, degrees);        //]
  Drivetrain.driveFor(reverse, 5, inches);  
  Drivetrain.turnFor(47, degrees);
  Drivetrain.setDriveVelocity(70, percent);
  Drivetrain.driveFor(reverse, 19, inches);
  Drivetrain.driveFor(forward, 10, inches);
  







  wait(50, msec);
  stopMotors();

  //forward turnRight  /// (Full length: forward) turnLeft forward (turn towards goal: turnleft) forward turnLeft forward ////
  //back up back in back up back in back up (turn toward goal: turnLeft) forward turnRight forward turnRight Forward backup

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
    resetCatapaultPosition = Controller1.ButtonUp.pressing(); // up arrow on dpad
    
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
    if(resetCatapaultPosition)
    {
      leftCatapault.spin(reverse);
      rightCatapault.spin(reverse);
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
  intakeOpen.spinToPosition(-150, degrees);
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

int catapaultAuton()
{
  timer Time = timer();
  Time.clear();
  float currentTime = Time.time(seconds);
  int catapaultMode = 0;
  while(currentTime < 45)
  {

    if(fabs(catapaultConstraint.position(degrees)) < 76)
    {
      leftCatapault.spin(forward);
      rightCatapault.spin(forward);
    }
    else if(fabs(catapaultConstraint.position(degrees)) > 76)
    {  
      if(catapaultMode % 2 == 0)
      {
        leftCatapault.stop();
        rightCatapault.stop();
        leftCatapault.setStopping(hold);
        rightCatapault.setStopping(hold);
      }
      else
      {
        intakeOpen.setPosition(0, degrees);
        openIntake();
        wait(500,msec);
        leftCatapault.setStopping(coast);
        rightCatapault.setStopping(coast);
        leftCatapault.spinFor(forward,100,degrees);
      }
    catapaultMode += 1;
    }
    else if(fabs((catapaultConstraint.position(degrees))) > 30)
    {

    }
  } 
  return 0;
}
void autonCatapaultFire()
{
  while(fabs(catapaultConstraint.position(degrees)) < 76)
  {

  }
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