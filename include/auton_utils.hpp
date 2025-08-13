#pragma once

#include <vector>
#include "main.h"

extern lemlib::Chassis chassis;

// Struct to hold the controller state at one moment
struct ControllerState
{
    int leftY;
    int leftX;
    int rightY;
    int rightX;
    bool btnA;
    bool btnB;
    bool btnX;
    bool btnY;
    // Add more buttons if you want
};

// Vector to hold the recording
extern std::vector<ControllerState> recordedInputs;

// Record current controller input (controller must NOT be const)
void recordControllerInput(pros::Controller &controller);

// Playback the recorded inputs — you must have 'chassis' defined elsewhere
void playbackRecordedInputs();

// Save/load recording to/from file on SD card (path like "/usd/skills_run.dat")
void saveRecordingToFile(const char *filename);
void loadRecordingFromFile(const char *filename);
