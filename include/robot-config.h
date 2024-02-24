using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern drivetrain Drivetrain;
extern motor leftIntake;
extern motor rightIntake;
extern motor leftCatapault;
extern motor rightCatapault;
extern motor_group intakeOpen;
extern rotation catapaultConstraint;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );