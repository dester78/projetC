#ifndef STRUCTURES
#define STRUCTURES
#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>

typedef struct Files{

    char *fullName;
    char  openMode[4];
    FILE *filePointer;

}Files;


typedef struct DbConfig{

    char* host;
    char* user;
    char* passwd;
    char* db;


}DbConfig;

typedef struct SDLConfig{

    
    struct SDLWindowConfig *window;
    struct SDLInitConfig *init;
    
    
}SDLConfig;


typedef struct SDLWindowConfig{

    long unsigned windowFlag;

}SDLWindowConfig;

typedef struct SDLInitConfig{

    long unsigned initFlag;

}SDLInitConfig;

// typedef struct SDLButtons{

//     SDL_Surface *buttonSurface; 
//     SDL_Rect *buttonPosition;
//     TTF_Font *textFont; 
    
//     SDL


// }SDLButtons;


//Fonctions d'initialisation de structures : 
int initDbConfig(DbConfig *dbConfigElement, char **arrayParameters,int lastRow );
void initSDLWindowConfig(SDLWindowConfig *windowConfigElement, char **arrayParameters,int lastRow );
void initSDLInitConfig(SDLInitConfig *initConfigElement, char **arrayParameters,int lastRow );
int initSDLConfig(SDLConfig *SDLConfigElement,char **arrayParameters,int lastRow );
Files returnFileElement(char *fullName, char* openMode);

//Fonctions de libération d'allocations de structures
void freeDbConfigElement(DbConfig *dbConfigElement );
void freeSDLConfigElement(SDLConfig *SDLConfigElement );
void freeFileElement(Files fileElement);


#endif 