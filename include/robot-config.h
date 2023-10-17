using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor leftRear;
extern motor leftMiddle;
extern motor leftFront;
extern motor rightRear;
extern motor rightMiddle;
extern motor rightFront;
extern motor leftIntake;
extern motor rightIntake;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );