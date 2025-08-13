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
#include "helpers.hpp"
#include "globals.hpp"
#include "auton_utils.hpp"

ASSET(BlueLeft1_txt);
ASSET(BlueLeft2_txt);

bool isRecording = false; // default off
const char *recordingFile = "/usd/skills_run.dat";

// Robodash auton selector
rd::Selector selector({{"Red Left", redLeftSide},
                       {"Red Right", redRightSide},
                       {"Blue Left", blueLeftSide},
                       {"Blue Right", blueRightSide},
                       {"Skills", skills},
                       {"Solo WP (Red)", soloWpRed},
                       {"Solo WP (Blue)", soloWpBlue},
                       {"Testing", testing}});

// Robodash image view
// rd_view_t *image_view = rd_view_create("Image");

// Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// TODO: replace these with updated motors for the new season
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

// TODO: Calculate this with the correct wheels and offsets
// horizontal tracking wheel. 2.75" diameter, 5.75" offset, back of the robot (negative)
// lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_275, -5.75);
// vertical tracking wheel. 2.75" diameter, 2.5" offset, left of the robot (negative)
lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_275, -2.5);

// Drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, &rightMotors, 14, lemlib::Omniwheel::OLD_275, 360, 2);

// TODO: Tune this
// Lateral motion controller
lemlib::ControllerSettings linearController(10, 0, 3, 3, 1, 100, 3, 500, 20);

// Angular motion controller
lemlib::ControllerSettings angularController(2, 0, 10, 3, 1, 100, 3, 500, 0);

// Sensors for odometry
lemlib::OdomSensors sensors(&vertical, nullptr, nullptr, nullptr, &imu);

// Input curves for driver control
lemlib::ExpoDriveCurve throttleCurve(3, 10, 1.019);
lemlib::ExpoDriveCurve steerCurve(3, 10, 1.019);

// Create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);

pros::Task colorSortTask(colorSortTaskFn);

// Match timer globals
uint32_t matchStartTime = 0;
const uint32_t matchDuration = 105000; // 1 min 45 sec match in ms

/**
 * Runs initialization code.
 */
void initialize()
{
    chassis.calibrate();                    // calibrate chassis
    optical_sensor.set_led_pwm(100);        // LED on for color detection
    optical_sensor.set_integration_time(5); // faster response
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

// Start the match timer
void startMatchTimer()
{
    matchStartTime = pros::millis();
}

// Display battery voltage on controller
void displayBatteryVoltage()
{
    float voltage = pros::battery::get_voltage(); // volts
    char buf[20];
    snprintf(buf, sizeof(buf), "Battery: %.2f V", voltage);
    controller.print(0, 0, buf);
}

// Display match timer countdown on controller
void displayMatchTimer()
{
    uint32_t elapsed = pros::millis() - matchStartTime;
    int remaining = (matchDuration - elapsed) / 1000; // seconds
    if (remaining < 0)
        remaining = 0;
    char buf[16];
    snprintf(buf, sizeof(buf), "Time: %02d:%02d", remaining / 60, remaining % 60);
    controller.print(1, 0, buf);
}

/**
 * Operator control code.
 */
void opcontrol()
{
    startMatchTimer();
    while (true)
    {
        // Update color sort stall detection
        checkIntakeStall();

        // Display battery voltage and timer
        displayBatteryVoltage();
        displayMatchTimer();

        // Retrieve joystick values for tank control.
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        chassis.tank(-leftY, -rightY);

        /*
        while (true)
        {
            // Toggle recording with a button press (example: X button)
            if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X))
            {
                isRecording = !isRecording;
                if (isRecording)
                {
                    recordedInputs.clear(); // start fresh
                    master.rumble(".");     // feedback
                }
                else
                {
                    saveRecordingToFile("/usd/skills.txt"); // save when stopping
                    master.rumble("-");                     // feedback
                }
            }
        */
       
        // Record controller inputs if enabled
        if (isRecording)
        {
            recordControllerInput(controller);
        }

            if (controller.get_digital(DIGITAL_B) && controller.get_digital(DIGITAL_DOWN)) // Have the auton run if we hit the B and Down button makes it so we don't need to have a comp switch to test autons
            {
                autonomous();
            }

            if (controller.get_digital(DIGITAL_UP))
            {
                intakeActive = true;
                optical_sensor.set_led_pwm(100);
            }

            if (controller.get_digital(DIGITAL_DOWN))
            {

                intakeActive = true;
                setIntake(115); // Reverse intake
            }

            if (controller.get_digital(DIGITAL_RIGHT))
            {
                intakeActive = false;
                setIntake(0); // Stop intake
            }
        }
}