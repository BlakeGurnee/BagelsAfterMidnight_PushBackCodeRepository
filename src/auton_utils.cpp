#include "auton_utils.hpp"
#include <cstdio>
#include "main.h" // For chassis reference

// Global vector of recorded inputs
std::vector<ControllerState> recordedInputs;

void recordControllerInput(pros::Controller &controller)
{
    ControllerState state;
    state.leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    state.leftX = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    state.rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    state.rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    state.btnA = controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);
    state.btnB = controller.get_digital(pros::E_CONTROLLER_DIGITAL_B);
    state.btnX = controller.get_digital(pros::E_CONTROLLER_DIGITAL_X);
    state.btnY = controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y);
    state.btnLeft = controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);
    state.btnRight = controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);
    state.btnUp = controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
    state.btnDown = controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
    state.btnL1 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
    state.btnL2 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
    state.btnR1 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
    state.btnR2 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

    recordedInputs.push_back(state);
}

void playbackRecordedInputs()
{
    for (const auto &state : recordedInputs)
    {
        // Make sure you have an extern lemlib::Chassis chassis declared somewhere accessible!
        chassis.tank(state.leftY, state.rightY);
        // Add other controls here if needed

        pros::delay(20); // Simulate controller polling delay
    }
}

void saveRecordingToFile(const char *filename)
{
    FILE *f = fopen(filename, "wb");
    if (!f)
    {
        pros::lcd::print(0, "Failed to open file for saving");
        return;
    }

    fwrite(recordedInputs.data(), sizeof(ControllerState), recordedInputs.size(), f);
    fclose(f);
}

void loadRecordingFromFile(const char *filename)
{
    FILE *f = fopen(filename, "rb");
    if (!f)
    {
        pros::lcd::print(0, "Recording file not found");
        return;
    }

    recordedInputs.clear();

    fseek(f, 0, SEEK_END);
    size_t fileSize = ftell(f);
    rewind(f);

    size_t numStates = fileSize / sizeof(ControllerState);
    recordedInputs.resize(numStates);

    fread(recordedInputs.data(), sizeof(ControllerState), numStates, f);
    fclose(f);
}
