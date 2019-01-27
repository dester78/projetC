#ifndef SDLTIMER
#define SDLTIMER

#include <SDLObjectsStructures.h>

#include <SDL.h>

// void refreshBackgroundHostMenu(SDLEnvironment *environment);
// void refreshBackgroundLevel(SDLEnvironment *environment);


void refreshBackground(SDLEnvironment *environment,MenuLevel menuOrLevel);
short controlUserEventTime(SDLEnvironment *environment);


#endif