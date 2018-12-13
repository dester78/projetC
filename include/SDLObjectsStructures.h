#ifndef SDLOBJECTSSTRUCTURES
#define SDLOBJECTSSTRUCTURES

#include <SDL.h>
#include <SDL_ttf.h>


typedef struct SDLContainer{

    SDL_Texture *texture; 
    SDL_Rect rect;
    SDL_Color color;

}SDLContainer;

typedef struct Triangle{

    SDL_Rect rect;
    int maxSize;

}Triangle;

typedef struct Square{

    SDL_Rect rect;
    int maxSize;

}Square; 

typedef struct Circle{

    int radius;
    int xCenter;
    int yCenter;
    int maxRadius; 

}Circle;

typedef struct MetroStation{

    int geometricShape;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect rect;

    Triangle triangle;
    Circle circle;
    Square square;

    Uint32 color;

}MetroStation;


typedef struct SDLBackground{

    SDL_Surface *surface;
    SDL_Texture *texture; 
    SDL_Rect rect;
    SDL_Color color;
    short sizeArrMetroStations;
    MetroStation **arrMetroStations;

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
void initMetroStation(MetroStation *metroStation, int geometricShape, SDL_Rect rect, int maxSize, Uint32 color);
Triangle initTriangle(SDL_Rect rect, int maxSize);
Circle initCircle(SDL_Rect rect, int maxSize);
Square initSquare(SDL_Rect rect, int maxSize);


void freeSDLButton(SDLButtons *sdlbuttonElement);
void freeSDLText(SDLText *sdlTextElement);

#endif