#include "main.h"
#include "globals.hpp"
#include "robodash/api.h"

void redLeftSide() // Red left auton scores number amount of points blah blah blah (replace)
{
  allianceIsRed = true;
  LOG("Running Red Left");
}

void redRightSide() // Red right auton scores number amount of points blah blah blah (replace)
{
  allianceIsRed = true;
  LOG("Running Red Right");
}

void blueLeftSide() // Blue Left auton scores number amount of points blah blah blah (replace)
{
  allianceIsRed = false;
  LOG("Running Blue Left");
}

void blueRightSide() // Blue right auton scores number amount of points blah blah blah (replace)
{
  allianceIsRed = false;
  LOG("Running Blue Right");
}

void soloWpBlue() // Auton for solo win point in case our teamate has a bad auton
{
  allianceIsRed = false;
  LOG("Running Solo Win Point Blue");
}

void soloWpRed() // Skills auton can get this many points with time amount of time left (replace)
{
  allianceIsRed = true;
  LOG("Running Solo Win Point Red");
}

void skills() // Skills auton can get this many points with time amount of time left (replace)
{
  allianceIsRed = true;
  LOG("Running Skills");
}

void testing() // Mode for testing only
{
  // allianceIsRed = true;
  // allianceIsRed = false;
  LOG("Testing Active");
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