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
    struct SDLRendererConfig *renderer;
    struct TTFConfig *ttf;

}SDLConfig;


typedef struct SDLWindowConfig{

    long unsigned windowFlag;

}SDLWindowConfig;

typedef struct SDLInitConfig{

    long unsigned initFlag;

}SDLInitConfig;

typedef struct SDLRendererConfig{

    long unsigned rendererFlag;

}SDLRendererConfig;

typedef struct TTFConfig{

    char *fontDirectory;
    char *fontMenu;

}TTFConfig;

typedef struct SDLButtons{

    SDL_Texture *buttonTexture; 
    SDL_Rect *buttonPosition;
    SDL_Color *buttonColor;
    SDLText *buttonText;
    
}SDLButtons;

typedef struct SDLText{

    SDL_Surface *textSurface;
    SDL_Texture *textTexture;
    SDL_Color *textColor; 
    TTF_Font *textFont;
    int sizeFont;
    char *textContent;
}SDLText;


//Fonctions d'initialisation de structures : 
int initDbConfig(DbConfig *dbConfigElement, char **arrayParameters,int lastRow );
void initSDLWindowConfig(SDLWindowConfig *windowConfigElement, char **arrayParameters,int lastRow );
void initSDLInitConfig(SDLInitConfig *initConfigElement, char **arrayParameters,int lastRow );
void initSDLRendererConfig(SDLRendererConfig *rendererConfigElement, char **arrayParameters,int lastRow );
void initTTFConfig(TTFConfig *ttfConfigElement, char **arrayParameters,int lastRow );
int initSDLConfig(SDLConfig *SDLConfigElement,char **arrayParameters,int lastRow );
Files returnFileElement(char *fullName, char* openMode);

//Fonctions de libération d'allocations de structures
void freeDbConfigElement(DbConfig *dbConfigElement );
void freeSDLConfigElement(SDLConfig *SDLConfigElement );
void freeFileElement(Files fileElement);


#endif 