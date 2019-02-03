#ifndef SDLMAIN
#define SDLMAIN

#include <structures.h>
#include <SDLConfigStructures.h>
#include <SDLObjectsStructures.h>

#include <SDL.h>
#include <mysql.h>


//Boucle principal du jeu
int SDLMainMenuLoop(SDL_Window  *mainWindow,SDL_Renderer *mainRenderer, SDLConfig *SDLConfigElement,DbConfig *dbConfigElement,MYSQL *dbConnection, FileIndex *FileIndex);


//Initialise les informations nécessaire à l'affichage des stations métro et lignes de métro dans le fond d'écan du menu
void addMetroLineAndStationMenu( SDLBackground *backgroundMenu,SDLButtons **buttonsHostMenu, unsigned short sizeArrayButtons );

//Boucle de niveau
short levelLoop(SDLEnvironment *environment, SDLConfig *SDLConfigElement,FileIndex *FileIndex, LevelName levelName, unsigned short difficulty);

// //Fonction modifiant un tableau en y intégrant les différents modes d'affichage disponibles sur l'écran 1 de l'utilisteur, elle retourne le nombre de mode disponibles
// int SDLGetArrayDisplayModes(SDL_DisplayMode **arrayDisplayModes);



//Créer un rectangle 
// SDL_Rect createCropRect(SDL_Rect foregroundRect, SDL_Rect backGroundRect);


// //Affiche les stations de métro dans le fond d'écran du menu
// short updateDisplayMetroStations(SDL_Renderer *mainRenderer, SDLBackground *backgroundMenu,SDLButtons **buttonsHostMenu, unsigned short sizeArrayButtons ,unsigned short countMetroStation);

// //Affiche les lignes de métro dans le fond d'écran du menu
// short updateDisplayMetroLineMenu(SDL_Renderer *mainRenderer, SDLBackground *backgroundMenu,SDLButtons **buttonsHostMenu, unsigned short sizeArrayButtons);

//void SDLAnimateBackgroundHostMenu( SDL_Surface **surface, SDL_Color newColor );

// //Eclairci un bouton du menu pour lui donner un effet de survol 
// void updateButtonColor(SDL_Renderer *mainRenderer, SDLButtons* button, SDL_Color buttonColor);
#endif