#include "main.h"
#include "globals.hpp"
#include "robodash/api.h"
#include "pros/motors.hpp"

// motors
// pros::MotorGroup rollers({4, 3}, pros::MotorGearset::green); // Rollers made up of two half motors // TODO: Raplace these with the right ports
pros::MotorGroup intake({5, 6}, pros::MotorGearset::green); // Intake made up of two half motors  // TODO: Raplace these with the right ports

// Pneumatics
pros::adi::Pneumatics flap1('A', true);  // Starts clamp in the false (Down) position when the code starts // TODO: Raplace these with the right ports
pros::adi::Pneumatics flap2('H', false); // Starts tipper in the false (Down) position when the code starts // TODO: Raplace these with the right ports

// Sensors
// Distance sensors
pros::Distance frontSensor(1); // Front distance sensor
pros::Distance leftSensor(2);  // left distance sensor
pros::Distance rightSensor(3); // right distance sensor

// Variables
// Set alliance color before match starts
bool allianceIsRed = true; // default, can change in auton select
bool intakeActive = false; // Start intake off
bool colorSortEnabled = true; // Color sort on by default


// Initialize devices
pros::Optical optical_sensor(1);
pros::Motor intakeMotor(2, pros::v5::MotorGears::green);

void initMotors()
{
    intakeMotor.set_reversed(false);
}

// Robodash console
rd::Console console;