#include "main.h"

extern pros::Controller controller;

void setIntake(int IntakePower);

void flap1Switch();
void flap2Switch();
void setIntake(int power);
void colorSortTaskFn();
void checkIntakeStall();
// Function to correct odometry using distance sensors
void correctOdomWithDistance();