#include "main.h"
#include "helpers.hpp"
#include "globals.hpp"
#include "pros/misc.hpp"
#include <numeric>

void setIntake(int intakePower)
{
    intake.move(intakePower);
}

// Background color sorting
void colorSortTaskFn()
{
    static int ejectState = 0;
    static uint32_t ejectStartTime = 0;

    const int intakeTime = 150;
    const int waitTime = 200;
    const int ejectTime = 350;
    const int proximityThreshold = 150;

    while (true)
    {
        if (!intakeActive)
        {
            setIntake(0);
            ejectState = 0;
            pros::delay(10);
            continue;
        }

        double hue = optical_sensor.get_hue();
        int proximity = optical_sensor.get_proximity();

        bool isBlue = (hue >= 190 && hue <= 250);
        bool isRed = (hue <= 20 || hue >= 340);
        bool wrongColor = false;

        if (proximity > proximityThreshold)
        {
            if (allianceIsRed && isBlue)
                wrongColor = true;
            if (!allianceIsRed && isRed)
                wrongColor = true;
        }

        switch (ejectState)
        {
        case 0:
            setIntake(-127);
            if (wrongColor)
            {
                ejectStartTime = pros::millis();
                ejectState = 1;
            }
            break;

        case 1:
            setIntake(-127);
            if (pros::millis() - ejectStartTime >= intakeTime)
            {
                ejectStartTime = pros::millis();
                ejectState = 2;
                setIntake(0);
            }
            break;

        case 2:
            if (pros::millis() - ejectStartTime >= waitTime)
            {
                ejectStartTime = pros::millis();
                ejectState = 3;
                setIntake(127);
            }
            break;

        case 3:
            if (pros::millis() - ejectStartTime >= ejectTime)
            {
                ejectState = 0;
                setIntake(-127);
            }
            break;
        }

        pros::delay(10); // small delay for CPU efficiency
    }
}

void flap1Switch()
{
    if (flap1.is_extended())
    {
        flap1.retract();
    }
    else
    {
        flap2.extend();
    }
}

void flap2Switch()
{
    if (flap2.is_extended())
    {
        flap2.retract();
    }
    else
    {
        flap2.extend();
    }
}

// Stall detection with auto-reverse
void checkIntakeStall()
{
    static int stallCounter = 0;
    static bool reversing = false;
    static uint32_t reverseStartTime = 0;

    const int stallThreshold = 20;      // number of checks below speed threshold before stall considered
    const int stallSpeedThreshold = 10; // below this velocity intake is considered stalled
    const int reverseDuration = 500;    // reverse duration in ms
    const int reversePower = 100;

    int intakeSpeed = intake.get_actual_velocity();

    if (reversing)
    {
        // Continue reversing for set duration
        if (pros::millis() - reverseStartTime >= reverseDuration)
        {
            reversing = false;
            stallCounter = 0;
            if (intakeActive)
                setIntake(-127); // Resume intake
            else
                setIntake(0);
        }
        else
        {
            setIntake(reversePower); // Reverse intake
        }
    }
    else
    {
        if (intakeActive && abs(intakeSpeed) < stallSpeedThreshold)
        {
            stallCounter++;
        }
        else
        {
            stallCounter = 0;
        }

        if (stallCounter > stallThreshold)
        {
            // Stall detected! Start reversing
            reversing = true;
            reverseStartTime = pros::millis();
            controller.rumble(".."); // Alert driver
        }
    }
}

// Correction thresholds (in meters or your preferred units)
const double FRONT_CORRECT_THRESHOLD = 0.05; // 5 cm
const double SIDE_CORRECT_THRESHOLD = 0.05;

// Rolling buffers for smoothing
std::array<double, SENSOR_BUFFER_SIZE> frontBuffer = {};
std::array<double, SENSOR_BUFFER_SIZE> leftBuffer = {};
std::array<double, SENSOR_BUFFER_SIZE> rightBuffer = {};
int bufferIndex = 0;

// Helper to compute average
double averageBuffer(const std::array<double, SENSOR_BUFFER_SIZE> &buf)
{
    double sum = std::accumulate(buf.begin(), buf.end(), 0.0);
    return sum / SENSOR_BUFFER_SIZE;
}

// Odometry correction function
void correctOdomWithDistance()
{
    if (!useOdomCorrection)
        return;

    // Add current sensor readings to buffers
    frontBuffer[bufferIndex] = frontSensor.get();
    leftBuffer[bufferIndex] = leftSensor.get();
    rightBuffer[bufferIndex] = rightSensor.get();

    // Update buffer index
    bufferIndex = (bufferIndex + 1) % SENSOR_BUFFER_SIZE;

    // Compute smoothed values
    double frontAvg = averageBuffer(frontBuffer);
    double leftAvg = averageBuffer(leftBuffer);
    double rightAvg = averageBuffer(rightBuffer);

    // Get current pose
    auto pose = chassis.getPose();

    // Correct X using front sensor
    double expectedFrontDistance = 0.0; // wall/reference distance
    double deltaX = frontAvg - expectedFrontDistance;
    if (fabs(deltaX) > FRONT_CORRECT_THRESHOLD)
    {
        pose.x += deltaX;
    }

    // Correct Y using side sensors
    double deltaY = 0.0;
    if (fabs(leftAvg - rightAvg) > SIDE_CORRECT_THRESHOLD)
    {
        deltaY = (leftAvg - rightAvg) / 2.0;
        pose.y += deltaY;
    }

    // Apply corrected pose
    chassis.setPose(pose);
}