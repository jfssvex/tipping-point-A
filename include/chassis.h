/**
 * \file chassis.h
 *
 * \brief Contains definition macros such as pin numbers.
 *
 * Contains definition macros such as pin numbers for a variety of
 * components (ex. motors, encoders) and dimensions.
 */

#pragma once

#include "driveSystems/drivetrainPID.h"

/*

Notes:
    - Ports 10 and 20 are dead

*/

// Motor pin numbers
#define TL_PORT 1
#define TR_PORT 9
#define BL_PORT 15
#define BR_PORT 19

#define INTAKE_PORT 12
#define FORKLIFT_PORT 11

// Encoder pin numbers
#define BENC_PORT_TOP 5
#define LENC_PORT_TOP 6
#define RENC_PORT_TOP 7

#define FORKLIFT_PORT_TOP 'G'

#define BENC_PORT_BOT 8
#define LENC_PORT_BOT 9
#define RENC_PORT_BOT 10

#define FORKLIFT_PORT_BOT 'H'

// Robot dimensions in inches (TODO: Update to real dimensions)
#define DRIVE_WHEEL_DIAMETER 3.25f
#define TRACKING_WHEEL_DIAMETER 2.75f
#define WHEELBASE 10.25f
#define BACK_WHEEL_OFFSET 5.0f