#ifndef SDLOBJECTSSTRUCTURES
#define SDLOBJECTSSTRUCTURES

#include <SDL.h>
#include <SDL_ttf.h>


typedef struct SDLContainer{

    SDL_Texture *texture; 
    SDL_Rect rect;
    SDL_Color color;

}SDLContainer;

typedef struct MetroStation{

    int radius;
    int xCenter;
    int yCenter; 
    Uint32 color;

}MetroStation;

typedef struct SDLBackground{

    SDL_Surface *surface;
    SDL_Texture *texture; 
    SDL_Rect rect;
    SDL_Color color;
    unsigned short sizeArrMetroStations;
    MetroStation *arrMetroStations[20];

}SDLBackground;


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
    char *fontPath;
    char *content;
}SDLText;



void initBackgroundHostMenu(SDL_Window *mainWindow,SDLBackground *backgroundHostMenu);
void initContainerHostMenu(SDL_Window* mainWindow,SDLContainer *containerHostMenu);
void initButtonsHostMenu(SDL_Window  *mainWindow, SDLContainer *containerHostMenu,SDLButtons** buttonsHostMenu, char *fontPath, int *sizeArrayButtons, int connectionState);
void initMetroStation(MetroStation *metroStation, int radius, int xCenter, int yCenter, Uint32 color);


void freeSDLButton(SDLButtons *sdlbuttonElement);
void freeSDLText(SDLText *sdlTextElement);

#endif