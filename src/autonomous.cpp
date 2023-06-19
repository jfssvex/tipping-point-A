#include "main.h"
#include "globals.h"

void testSystems() {
    forklift.goDown();
    intake.clockwise(100);

    // Wait to reach reasonable tolerance levels
    while (abs(forklift.getError() && intake.getError()) < 20) {
        pros::delay(10);
    };

    forklift.goUp();
    intake.counterClockwise(100);

    // Wait to reach reasonable tolerance levels
    while (abs(forklift.getError() && intake.getError()) < 20) {
        pros::delay(10);
    };
}
/* 
void BlueLeftCorner() {


    }

   
void BlueRightCorner() {
    
        
    }

void RedLeftCorner() {
    

    }

void RedRightCorner() {

        
    } 
*/

    void myAuton()
    {
        forklift.enable();
        intake.enable();

        // testSystems();   
        //  BlueLeftCorner();
        //  BlueRightCorner();
        //  RedLeftCorner();
        //  RedRightCorner();
    }

//TODO: Add a proper auton selector that uses the LCD screen