#ifndef SDLOBJECTSSTRUCTURES
#define SDLOBJECTSSTRUCTURES

#include<SDLConfigStructures.h>

#include <SDL.h>
#include <mysql.h>
#include <SDL_ttf.h>




typedef struct SDLText{

    SDL_Surface *surface;
    SDL_Texture *texture;
    TTF_Font *font;
    SDL_Color color; 
    SDL_Rect rect;

    unsigned short sizeFont;
    char *fontPath;
    char *content;
}SDLText;


typedef struct SDLButtons{

    SDL_Texture *texture; 
    SDL_Rect rect;
    SDL_Color color;

    SDLText *text;
    
}SDLButtons;


typedef struct SDLContainer{

    unsigned short sizeArrayButtons;
    unsigned short sizeArrayText;

    SDLButtons **arrayButtons;
    SDLText *text;

    SDL_Texture *texture; 
    SDL_Rect rect;
    SDL_Color color;

}SDLContainer;


typedef struct SDLGUI{

    SDLContainer *container;
    
}SDLGUI;


typedef struct Triangle{

    SDL_Rect rect;
    unsigned short maxSize;

}Triangle;

typedef struct Square{

    SDL_Rect rect;
    unsigned short maxSize;

}Square; 

typedef struct Circle{

    unsigned short radius;
    unsigned int xCenter;
    unsigned int yCenter;
    unsigned short maxRadius; 

}Circle;

typedef struct MetroStation{

    unsigned short geometricShape;
    unsigned short maxSize;
    unsigned short overlapRisk;

    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect rect;
    SDL_Rect overlapRect;
    SDL_Color *arrLinesColor;

    Triangle triangle;
    Circle circle;
    Square square;

    Uint32 color;

}MetroStation;

typedef struct MetroLine{

    unsigned short width;

    SDL_Texture *texture;
    SDL_Rect rect; 
    SDL_Point srcPoint; 
    SDL_Point dstPoint; 
    
    Uint32 color;

}MetroLine;


typedef struct SDLBackground{

    SDL_Surface *surface;
    SDL_Texture *texture; 
    SDL_Rect rect;
    SDL_Color color;

    unsigned short sizeArrMetroLinesColor; 
    unsigned short sizeArrMetroStations;
    unsigned short sizeArrMetroLines;

    SDL_Color *arrMetroLinesColor;
    MetroStation **arrMetroStations;
    MetroLine **arrMetroLines;

}SDLBackground;




void initGUIHostMenu(SDL_Window  **mainWindow,SDLGUI *guiHostMenu, SDLConfig *SDLConfigElement,MYSQL *dbConnection);
void initBackgroundHostMenu(SDL_Window **mainWindow,SDLBackground **backgroundHostMenu);
void initContainerHostMenu(SDL_Window** mainWindow,SDLContainer *containerHostMenu,SDLConfig *SDLConfigElement,MYSQL *dbConnection);
void initButtonsHostMenu(SDL_Window  **mainWindow, SDLContainer *containerHostMenu,SDLButtons** buttonsHostMenu, char *fontPath, unsigned short sizeArrayButtons, short connectionState);
void initMetroStation(MetroStation *metroStation, unsigned short geometricShape, SDL_Rect rect, unsigned short maxSize, Uint32 color);
void initMetroLine(MetroLine *metroLine, SDL_Rect rect, Uint32 color);


Triangle initTriangle(SDL_Rect rect, unsigned short maxSize);
Circle initCircle(SDL_Rect rect, unsigned short maxSize);
Square initSquare(SDL_Rect rect, unsigned short maxSize);

void freeSDLButton(SDLButtons *sdlbuttonElement);
void freeSDLText(SDLText *sdlTextElement);

#endif