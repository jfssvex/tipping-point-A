/**
 * Implementation for the Forklift system manager.
*/

#include "systems/fork.h"
#include "systems/systemManager.h"

forkMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

void Fork::up() {
    forkMotor.move(-FORK_POWER);
}

void Fork::down() {
    forkMotor.move(FORK_POWER);
}

void Fork::stop() {
    forkMotor.move(0);
}

void Fork::update() {
    // Update PID variables
    this->position = this->forkMotor.get_position();
    this->error = this->position - this->target;
}

void Fork::fullReset() {
    this->forkMotor.tare_position();
    SystemManager::fullReset();
}