#include "main.h"
#include "globals.h"
#include "macros.h"

/**
 * \brief Scale joystick output to cubic graph
 * 
 * Scales raw value in range [-127, 127] to range [-1, 1] and apply exponent 3 in order to allow for more driver accuracy
*/
double joystickCubicDrive(int raw) {
    double scaledRaw = ((double)raw) / 127.0;
    return pow(scaledRaw, 3) * 127;
}

void myOpControl() {
    // Enable the systems
    intake.enable();
    forklift.enable();

    // 0 -> nothing, 1 -> clockwise, -1 -> counter clockwise
    int macroToggle = 0;

    while (true) {
        // Basic op control using arcade drive
        int forward = masterController.get_analog(ANALOG_LEFT_Y);
        int sideways = masterController.get_analog(ANALOG_LEFT_X);
        driveTrain->arcade(joystickCubicDrive(forward), joystickCubicDrive(sideways), 0);

        int intakeUp = masterController.get_digital(DIGITAL_R1);
        int intakeDown = masterController.get_digital(DIGITAL_R2);

        /*
        // For experimenting with speeds
        int intakeSpeed2 = masterController.get_digital(DIGITAL_L2);
        int intakeSpeed3 = masterController.get_digital(DIGITAL_R2);
        */
       
        int intakeMacroCW = masterController.get_digital_new_press(DIGITAL_UP);
        int intakeMacroCCW = masterController.get_digital_new_press(DIGITAL_DOWN);

        bool forkUp = masterController.get_digital(DIGITAL_L1);
		bool forkDown = masterController.get_digital(DIGITAL_L2);

        // Intake macro handler
        if (macroToggle == -1 && intakeMacroCCW) {
            // Turn off macro
            macroToggle = 0;
        } else if (macroToggle == 1 && intakeMacroCW) {
            // Turn off macro
            macroToggle = 0;
        } else {
            // State does not match the button pressed, enable the respective macro
            if (intakeMacroCW) {
                // Change macro state to clockwise
                macroToggle = 1;
            } else if (intakeMacroCCW) {
                // Change macro state to counter clockwise
                macroToggle = -1;
            }
        }

        // Apply macro control to intake system
        switch (macroToggle) {
            case 1: {
                startIntakeSmoothMove(false, false);
                break;
            }
            case -1: {
                startIntakeSmoothMove(true, true);
                break;
            }
            case 0: {
                // Operator control
                intake.control();

                if (intakeUp) {
                    intake.setPower(90);
                } else if (intakeDown) {
                    intake.setPower(-90);
                } else {
                    intake.setPower(0);
                }

                // Joystick now mapped to intake, change later
                //intake.setPower(joystickCubicDrive(intakeUp));
                break;
            }
            default: {
                break;
            }
        }

        // Operator control
        if (!macroToggle) {
            stopIntakeSmoothMove();
        }

        if(forkUp){
			forklift.up();
		}
		else if(forkDown){
			forklift.down();
		}
		else{
			forklift.stop();
		}


		pros::delay(20);
	}
}