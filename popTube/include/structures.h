#ifndef STRUCTURES
#define STRUCTURES

#include <stdio.h>

#include <SDL.h>
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
    char* playerLogin;
    char* playerPasswd;


}DbConfig;

typedef struct SDLConfig{

    
    struct SDLWindowConfig *window;
    struct SDLInitConfig *init;
    struct SDLRendererConfig *renderer;
    struct TTFConfig *ttf;

}SDLConfig;


typedef struct SDLWindowConfig{

    unsigned int windowFlag;
    int windowHeight;
    int windowWidth;

}SDLWindowConfig;

typedef struct SDLInitConfig{

    unsigned int initFlag;

}SDLInitConfig;

typedef struct SDLRendererConfig{

    unsigned int rendererFlag;

}SDLRendererConfig;

typedef struct TTFConfig{

    char *fontDirectory;
    char *fontMenu;

}TTFConfig;

typedef struct SDLContainer{

    SDL_Texture *texture; 
    SDL_Rect rect;
    SDL_Color color;

}SDLContainer;

typedef struct SDLButtons{

    SDL_Texture *texture; 
    SDL_Rect rect;
    SDL_Color color;
    struct SDLText *text;
    
}SDLButtons;

typedef struct SDLText{

    SDL_Surface *surface;
    SDL_Texture *texture;
    TTF_Font *font;
    SDL_Color color; 
    SDL_Rect rect;
    int sizeFont;
    char *content;
}SDLText;


//Fonctions d'initialisation de structures : 
int initDbConfig(DbConfig *dbConfigElement, char **arrayParameters,int lastRow );
void initSDLWindowConfig(SDLWindowConfig *windowConfigElement, char **arrayParameters,int lastRow );
void initSDLInitConfig(SDLInitConfig *initConfigElement, char **arrayParameters,int lastRow );
void initSDLRendererConfig(SDLRendererConfig *rendererConfigElement, char **arrayParameters,int lastRow );
void initTTFConfig(TTFConfig *ttfConfigElement, char **arrayParameters,int lastRow );
int initSDLConfig(SDLConfig *SDLConfigElement,char **arrayParameters,int lastRow );
Files returnFileElement(char *fullName, char* openMode);

//Fonctions de liberation d'allocations de structures
void freeDbConfigElement(DbConfig *dbConfigElement );
void freeSDLConfigElement(SDLConfig *SDLConfigElement );
void freeFileElement(Files fileElement);


#endif 