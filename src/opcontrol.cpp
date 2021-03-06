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

    // Enable all systems
    intake.enable();
    forklift.enable();

    // 0 -> nothing, 1 -> clockwise, -1 -> counter clockwise
    int macroToggle = 0;

    // Internal state for forklift 1
    // 0 -> Down, 1 -> Middle, 2 -> Up
    int forkliftState = 0;

    while (true) {
        // Basic op control using arcade drive
        int forward = masterController.get_analog(ANALOG_LEFT_Y);
        int sideways = masterController.get_analog(ANALOG_LEFT_X);

        driveTrain->arcade(joystickCubicDrive(forward), joystickCubicDrive(sideways), 0);

         // Intake mapped to right shoulder buttons
        int intakeUp = masterController.get_digital(DIGITAL_R1);
        int intakeDown = masterController.get_digital(DIGITAL_R2);
        
        // Forklift mapped to right joystick up and down
        int forkliftSpeed;
        int forkliftState = -(masterController.get_analog(ANALOG_RIGHT_Y));

        // Forklift mapped to right joystick up and down
        if (forkliftEnc.get_value() < 45) {
            // Forklift will only move up while it is less than 200 ticks
            forkliftSpeed = -(masterController.get_analog(ANALOG_RIGHT_Y));
        }
        else if (forkliftEnc.get_value() >= 45 && forkliftState > 0) {
            forkliftSpeed = 0;
        }
        else if (forkliftEnc.get_value() >= 45 && forkliftState < 0) {
            forkliftSpeed = -(masterController.get_analog(ANALOG_RIGHT_Y));
        }
        
        /*
        float forkliftUp = masterController.get_digital(DIGITAL_L1);
        
        if (forkliftUp) {
            if (forkliftEnc.get_value() < 30) {
                forklift.setPower(-0.01);
            }
            else if (forkliftEnc.get_value() >= 30) {
                forklift.setPower(0);
            }
        }
        */
        // Fix deadzone issue, value might need tuning
        if (abs(forkliftSpeed) < 30) {
            forkliftSpeed = 0;
        }

       // Macros are set to up and down buttons
        int intakeMacroCW = masterController.get_digital_new_press(DIGITAL_UP);
        int intakeMacroCCW = masterController.get_digital_new_press(DIGITAL_DOWN);

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
                 //TODO: Update value 
                int intakeSpeed = 100;

                if (intakeUp) {
                    intake.setPower(intakeSpeed);
                }
                else if (intakeDown) {
                    intake.setPower(-(intakeSpeed));
                }
                else {
                    intake.setPower(0);
                }
            }
            default: {
                break;
            }
        }
        intake.update();

        // Forklift control
        forklift.control();
        
        forklift.setPower(forkliftSpeed);

        // Run update funcs on sysmans
        forklift.update();

        // Operator control
        if (!macroToggle) {
            stopIntakeSmoothMove();
        }

        pros::delay(10);
    }    
}