#ifndef SDLTIMER
#define SDLTIMER

#include <SDLObjectsStructures.h>
#include <SDLMetroStation.h>

#include <SDL.h>

// void refreshBackgroundHostMenu(SDLEnvironment *environment);
// void refreshBackgroundLevel(SDLEnvironment *environment);

//Fonction chargée de rafraichir le background du jeu selon une fréquence de raffraichissement, la fonction est utilisée dans le cas du menu ou d'un niveau. 
void refreshBackground(SDLEnvironment *environment,MenuLevel menuOrLevel);

//Fonction se chargeant de valider ou non des évenements généré par les utilisateurs si ils répondent à une durée défini dans la structure Timer
short controlUserEventTime(SDLEnvironment *environment);


#endif