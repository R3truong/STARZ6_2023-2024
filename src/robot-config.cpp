#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor RearRight = motor(PORT20, ratio18_1, true);
motor RearLeft = motor(PORT11, ratio18_1, false);
motor CenterRight = motor(PORT19, ratio18_1, true);
motor CenterLeft = motor(PORT12, ratio18_1, false);
motor FrontRight = motor(PORT10, ratio18_1, true);
motor FrontLeft = motor(PORT1, ratio18_1, false);
inertial InertiaSensor = inertial(PORT5);
motor rightIntake = motor(PORT6, ratio18_1, false);
motor leftIntake = motor(PORT13, ratio18_1, false);
motor rightClawSpin = motor(PORT9, ratio18_1, false);
motor leftClawSpin = motor(PORT18, ratio18_1, false);
motor leftCatapault = motor(PORT4, ratio18_1, true);
motor rightCatapault = motor(PORT3, ratio18_1, false);
limit catapaultSwitch = limit(Brain.ThreeWirePort.A);

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