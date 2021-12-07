/**
 * \file fork.h
 * 
 * \brief Contains headers for the Forklift system manager.
*/

#pragma once

#include "main.h"
#include "systemManager.h"
#include "chassis.h"

#define FORK_POWER = 127;

/**
 * \brief Forklift system manager class, inherits from SystemManager. 
*/
class Fork: public SystemManager {
    public:
        /**
         * Move the motor for the forklift upwards
        */
        void up();

        /**
         * Move the motor for the forklift dowmwards
        */
        void down();

        /**
         * Stop moving the forklift
         */
        void stop();

        /**
         * The control loop for the system. This should be run every loop.
        */
        void update() override;

        /**
         * Run a full reset of the system and its variables and state.
        */
        void fullReset() override;

    protected:
        // Forklift motor
        pros::Motor forkMotor = pros::Motor(FORK_PORT);
}