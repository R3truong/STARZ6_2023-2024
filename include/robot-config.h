using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor RearRight;
extern motor RearLeft;
extern motor CenterRight;
extern motor CenterLeft;
extern motor FrontRight;
extern motor FrontLeft;
extern inertial InertiaSensor;
extern motor rightIntake;
extern motor leftIntake;
extern motor rightClawSpin;
extern motor leftClawSpin;
extern motor leftCatapault;
extern motor rightCatapault;
extern limit catapaultSwitch;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );