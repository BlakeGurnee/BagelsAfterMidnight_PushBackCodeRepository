// Include all necessary headers
#include "main.h"
#include "lemlib/api.hpp"
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
#include "auton_utils.hpp"

// Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Motor groups
pros::MotorGroup leftMotors({-3, -2, -20}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({1, 5, 9}, pros::MotorGearset::blue);

// IMU
pros::Imu imu(7);

// Tracking wheels
pros::Rotation horizontalEnc(20);
pros::Rotation verticalEnc(-11);

lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_275, -2.5);

// Drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, &rightMotors, 14, lemlib::Omniwheel::OLD_275, 360, 2);

// Controllers
lemlib::ControllerSettings linearController(10, 0, 3, 3, 1, 100, 3, 500, 20);
lemlib::ControllerSettings angularController(2, 0, 10, 3, 1, 100, 3, 500, 0);

// Sensors for odometry
lemlib::OdomSensors sensors(&vertical, nullptr, nullptr, nullptr, &imu);

// Input curves
lemlib::ExpoDriveCurve throttleCurve(3, 10, 1.019);
lemlib::ExpoDriveCurve steerCurve(3, 10, 1.019);

// Chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);

// Robodash auton selector
rd::Selector selector({{"Red Left", redLeftSide},
                       {"Red Right", redRightSide},
                       {"Blue Left", blueLeftSide},
                       {"Blue Right", blueRightSide},
                       {"Skills", skills},
                       {"Solo WP (Red)", soloWpRed},
                       {"Solo WP (Blue)", soloWpBlue},
                       {"Testing", testing}});

// Match timer
uint32_t matchStartTime = 0;
const uint32_t matchDuration = 105000; // 1:45

// Controller input recording
bool isRecording = false;
const char *recordingFile = "/usd/skills_run.dat";

// Flag to enable odometry correction
bool useOdomCorrection = false;

// Helper function to run odometry correction periodically
void maybeCorrectOdom()
{
    static uint32_t lastCorrection = 0;
    if (useOdomCorrection && pros::millis() - lastCorrection > 100)
    {
        correctOdomWithDistance(); // defined in helpers
        lastCorrection = pros::millis();
    }
}

void initialize()
{
    chassis.calibrate();
    optical_sensor.set_led_pwm(100);
    optical_sensor.set_integration_time(5);
}

void disabled() {}

void competition_initialize() {}

void startMatchTimer()
{
    matchStartTime = pros::millis();
}

void displayBatteryVoltage()
{
    float voltage = pros::battery::get_voltage();
    char buf[20];
    snprintf(buf, sizeof(buf), "Battery: %.2f V", voltage);
    controller.print(0, 0, buf);
}

void displayMatchTimer()
{
    uint32_t elapsed = pros::millis() - matchStartTime;
    int remaining = (matchDuration - elapsed) / 1000;
    if (remaining < 0)
        remaining = 0;
    char buf[16];
    snprintf(buf, sizeof(buf), "Time: %02d:%02d", remaining / 60, remaining % 60);
    controller.print(1, 0, buf);
}

void autonomous()
{
    useOdomCorrection = true; // enable correction
    selector.run_auton();
    useOdomCorrection = false; // turn off after auton finishes
}

void opcontrol()
{
    startMatchTimer();
    while (true)
    {
        // Update stall detection
        checkIntakeStall();

        // Display battery & timer
        displayBatteryVoltage();
        displayMatchTimer();

        // Tank drive
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        chassis.tank(-leftY, -rightY);

        // Controller input recording
        if (isRecording)
        {
            recordControllerInput(controller);
        }

        // Example intake controls
        if (controller.get_digital(DIGITAL_UP))
        {
            intakeActive = true;
            optical_sensor.set_led_pwm(100);
        }
        else if (controller.get_digital(DIGITAL_DOWN))
        {
            intakeActive = true;
            setIntake(115);
        }
        else if (controller.get_digital(DIGITAL_RIGHT))
        {
            intakeActive = false;
            setIntake(0);
        }

        // Optionally trigger auton from driver control (for testing)
        if (controller.get_digital(DIGITAL_B) && controller.get_digital(DIGITAL_DOWN))
        {
            autonomous();
        }

        pros::delay(10);
    }
}
