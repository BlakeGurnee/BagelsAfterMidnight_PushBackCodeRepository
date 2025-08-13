#include "main.h"
#include "helpers.hpp"
#include "globals.hpp"
#include "pros/misc.hpp"

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