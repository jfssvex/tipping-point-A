#include "main.h"
#include "globals.h"

/**
 * \brief Scale joystick output to cubic graph
 * 
 * Scales raw value in range [-127, 127] to range [-1, 1] and apply exponent 3 in order to allow for more driver accuracy
*/
double joystickCubicDrive(int raw) {
    double scaledRaw = ((double)raw) / 127.0;
    return pow(scaledRaw, 3);
}

void myOpControl()
{
    // Basic op control using tank drive
    while (true)
    {
        pros::delay(10);
        int power = masterController.get_analog(ANALOG_LEFT_Y);
        int turn = masterController.get_analog(ANALOG_RIGHT_X);

        driveTrain->tank(joystickCubicDrive(power), joystickCubicDrive(turn), 0.5); // TODO: Change threshold to something useful
    }
}