#ifndef SDLMAIN
#define SDLMAIN

#include <structures.h>
#include <SDLConfigStructures.h>
#include <SDLObjectsStructures.h>

#include <SDL.h>
#include <mysql.h>

/*
 * ─── INITIALISATION DES BOUCLES ─────────────────────────────────────────────────
 */

//Initialisation des éléments nécessaire à la boucle de menu
SDLEnvironment *initMainMenuLoop(SDL_Window  *mainWindow, SDL_Renderer *mainRenderer, SDLConfig *SDLConfigElement,MYSQL *dbConnection);

//Initialisation des éléments nécessaire à la boucle de niveau
short initLeveLLoop(SDLEnvironment *environment, SDLConfig *SDLConfigElement,FileIndex *fileIndex, LevelName levelName, unsigned short difficulty);


/*
 * ─── BOUCLES SDL ────────────────────────────────────────────────────────────────
 */

//Boucle principal du jeu
int SDLMainMenuLoop(SDL_Window  *mainWindow,SDL_Renderer *mainRenderer, SDLConfig *SDLConfigElement,DbConfig *dbConfigElement,MYSQL *dbConnection, FileIndex *FileIndex);

//Boucle de niveau
short levelLoop(SDLEnvironment *environment, SDLConfig *SDLConfigElement,FileIndex *FileIndex, LevelName levelName, unsigned short difficulty);


#endif