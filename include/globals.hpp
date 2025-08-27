#include "main.h"
#pragma once
#include "robodash/api.h"
#include "pros/adi.hpp"
#include "pros/optical.hpp"
#include "pros/motors.hpp"

// motors
extern pros::MotorGroup intake;
extern pros::Motor intakeMotor;

// pneumatics
//extern pros::adi::Pneumatics flap1; commented out until we add the Pneumatics

// Sensors
// Distance?
extern pros::Optical optical_sensor;

// Variables

// Global flags
extern bool allianceIsRed;
extern bool intakeActive;
extern bool colorSortEnabled;

extern rd::Console console;
#define LOG(...) console.print(__VA_ARGS__) // define a log function for easier printing to the console
