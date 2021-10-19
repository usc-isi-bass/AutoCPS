/*
 * Common FSW parameters, autogenerated by Python
 */

#ifndef PARAMS_H
#define PARAMS_H

#include "datatypes.h"

enum SystemType = {ROVER, PLANE, ROCKET, HELICOPTER};

// Global
#define MASS         125.0
#define DIMENSIONS   {0.0, 0.0, 0.0}

// Plane-only
#define ENGINES      {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}

// Rover-only
#define MOTORS       {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}
#define MOTOR_SPEEDS {0.0, 0.0}

// Rocket-only
#define I_SP         100.0
#define MAX_FUEL     100.0
#define BURN_RATE    100.0

// Helicopter-only
#define PROPELLERS   {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}
#define PROP_THRUSTS {0.0, 0.0}

#endif
