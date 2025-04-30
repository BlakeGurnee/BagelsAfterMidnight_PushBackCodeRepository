#include "main.h"
#include "robodash/api.h"

// Robodash console
rd::Console consoleLog;

void redLeftSide() // Red left auton scores number amount of points blah blah blah (replace)
{
  consoleLog.print("Running Red Left");
}

void redRightSide() // Red right auton scores number amount of points blah blah blah (replace)
{
  consoleLog.print("Running Red Right");
}

void blueLeftSide() // Blue Left auton scores number amount of points blah blah blah (replace)
{
  consoleLog.print("Running Blue Left");
}

void blueRightSide() // Blue right auton scores number amount of points blah blah blah (replace)
{
  consoleLog.print("Running Blue Right");
}

void soloWP() // Auton for solo win point in case our teamate has a bad auton
{
  consoleLog.print("Running Solo Win Point");
}

void skills() // Skills auton can get this many points with time amount of time left (replace)
{
  consoleLog.print("Running Skills");
}

void testing() // Mode for testing only
{
  consoleLog.print("Testing Active");
}

/* Eliminate Round autons these autons are different from regular autons becuase in the elimination rounds you don't need to worry about getting winpoint
so these autons are made to get the most points possible and setting us up for the match without having to worry about win point
(These are usually commented out until the elimitantion rounds then I uncomment all of these so they will work)

void redLeftSide() // Red left auton scores number amount of points blah blah blah (replace)
{
  consoleLog.println("Running Red Left");
}

void redRightSide() // Red right auton scores number amount of points blah blah blah (replace)
{
  consoleLog.println("Running Red Right");
}

void blueLeftSide() // Blue Left auton scores number amount of points blah blah blah (replace)
{
  consoleLog.println("Running Blue Left");
}

void blueRightSide() // Blue right auton scores number amount of points blah blah blah (replace)
{
  consoleLog.println("Running Blue Right");
}

*/