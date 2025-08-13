#include "main.h"
#pragma once
#include "robodash/api.h"
#include "pros/adi.hpp"
#include "pros/optical.hpp"
#include "pros/motors.hpp"

// motors
extern pros::MotorGroup intake;

// pneumatics
extern pros::adi::Pneumatics flap1;
extern pros::adi::Pneumatics flap2;

// Sensors

// Variables

// Global flags
extern bool allianceIsRed;
extern bool intakeActive;
extern bool colorSortEnabled;

// Global devices
extern pros::Optical optical_sensor;
extern pros::Motor intakeMotor;


extern rd::Console console;
#define LOG(...) console.print(__VA_ARGS__) // define a log function for easier printing to the console
