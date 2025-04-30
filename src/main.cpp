// Include all neccesarry Headers
#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "autons.hpp"
#include "globals.hpp"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pros/llemu.hpp"
#include "pros/apix.h"
#include "robodash/api.h"

ASSET(BlueLeft1_txt);
ASSET(BlueLeft2_txt);

// Robodash auton selector
rd::Selector selector({{"Red Left", redLeftSide},
                       {"Red Right", redRightSide},
                       {"Blue Left", blueLeftSide},
                       {"Blue Right", blueRightSide},
                       {"Skills", skills},
                       {"Testing", testing}});

// Robodash image view
// rd_view_t *image_view = rd_view_create("Image");

// Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Motor groups
pros::MotorGroup leftMotors({-3, -2, -20}, pros::MotorGearset::blue); // left motor group
pros::MotorGroup rightMotors({1, 5, 9}, pros::MotorGearset::blue);    // right motor group

// Imu on port 7
pros::Imu imu(7);

// tracking wheels
// horizontal tracking wheel encoder. Rotation sensor, port 20, not reversed
pros::Rotation horizontalEnc(20);
// vertical tracking wheel encoder. Rotation sensor, port 11, reversed
pros::Rotation verticalEnc(-11);
// horizontal tracking wheel. 2.75" diameter, 5.75" offset, back of the robot (negative)
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_275, -5.75);
// vertical tracking wheel. 2.75" diameter, 2.5" offset, left of the robot (negative)
lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_275, -2.5);

// Drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, &rightMotors, 14, lemlib::Omniwheel::OLD_275, 360, 2);

// Lateral motion controller
lemlib::ControllerSettings linearController(10, 0, 3, 3, 1, 100, 3, 500, 20);

// Angular motion controller
lemlib::ControllerSettings angularController(2, 0, 10, 3, 1, 100, 3, 500, 0);

// Sensors for odometry
lemlib::OdomSensors sensors(&vertical, nullptr, &horizontal, nullptr, &imu);

// Input curves for driver control
lemlib::ExpoDriveCurve throttleCurve(3, 10, 1.019);
lemlib::ExpoDriveCurve steerCurve(3, 10, 1.019);

// Create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);

/**
 * Runs initialization code.
 */
void initialize()
{
    chassis.calibrate(); // calibrate chassis
    // You can include other initialization code here as needed.
}

/**
 * Runs while the robot is disabled.
 */
void disabled() {}

/**
 * Runs competition initialization routines.
 */
void competition_initialize() {}

/**
 * Autonomous routine.
 */

void autonomous()
{

    // Run selected autonomous
    selector.run_auton();
}

/**
 * Operator control code.
 */
void opcontrol()
{
    while (true)
    {
        // Retrieve joystick values for tank control.
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        chassis.tank(-leftY, -rightY);

        if (controller.get_digital(DIGITAL_B) && controller.get_digital(DIGITAL_DOWN))
        { // Have the auton run if we hit the B and Down button makes it so we don't need to have a comp switch to test autons
            autonomous();
        }
    }
}