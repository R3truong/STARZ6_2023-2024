#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor leftRear = motor(PORT11, ratio18_1, false);
motor leftMiddle = motor(PORT1, ratio18_1, false);
motor leftFront = motor(PORT2, ratio18_1, true);
motor rightRear = motor(PORT20, ratio18_1, true);
motor rightMiddle = motor(PORT10, ratio18_1, true);
motor rightFront = motor(PORT9, ratio18_1, false);
motor leftIntake = motor(PORT5, ratio18_1, false);
motor rightIntake = motor(PORT6, ratio18_1, true);

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