using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor RearLeft;
extern motor CenterRight;
extern inertial InertiaSensor;
extern motor rightIntake;
extern motor leftIntake;
extern motor leftCatapault;
extern motor rightCatapault;
extern limit catapaultSwitch;
extern motor RearRight;
extern motor CenterLeft;
extern motor FrontLeft;
extern motor FrontRight;
extern motor_group intakeOpen;
extern rotation catapaultConstraint;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );