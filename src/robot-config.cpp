#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor RearLeft = motor(PORT9, ratio18_1, true);
motor CenterRight = motor(PORT21, ratio18_1, true);
inertial InertiaSensor = inertial(PORT5);
motor rightIntake = motor(PORT20, ratio18_1, true);
motor leftIntake = motor(PORT2, ratio18_1, true);
motor rightClawSpin = motor(PORT17, ratio18_1, false);
motor leftClawSpin = motor(PORT18, ratio18_1, false);
motor leftCatapault = motor(PORT8, ratio18_1, false);
motor rightCatapault = motor(PORT10, ratio18_1, true);
limit catapaultSwitch = limit(Brain.ThreeWirePort.H);
motor RearRight = motor(PORT1, ratio18_1, false);
motor CenterLeft = motor(PORT12, ratio18_1, true);
motor FrontLeft = motor(PORT13, ratio18_1, true);
motor FrontRight = motor(PORT11, ratio18_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}