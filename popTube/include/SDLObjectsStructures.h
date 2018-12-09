#ifndef SDLOBJECTSSTRUCTURES
#define SDLOBJECTSSTRUCTURES

#include <SDL.h>
#include <SDL_ttf.h>


typedef struct SDLContainer{

    SDL_Texture *texture; 
    SDL_Rect rect;
    SDL_Color color;

}SDLContainer;

typedef struct SDLBackground{

    SDL_Texture *texture; 
    SDL_Rect rect;
    SDL_Color color;

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

void freeSDLButton(SDLButtons *sdlbuttonElement);
void freeSDLText(SDLText *sdlTextElement);

#endif