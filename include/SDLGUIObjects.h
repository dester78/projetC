#ifndef SDLGUIOBJECTS
#define SDLGUIOBJECTS

#include <SDLObjectsStructures.h>

#include <SDL.h>

void displayTextButton(SDL_Renderer *mainRenderer, SDLButtons* buttonHostMenu);
void displayContainer(SDL_Renderer *mainRenderer,SDLContainer *container);
void displayRectButton(SDL_Renderer *mainRenderer,SDLButtons* button);
void displayButtonInCircle(SDL_Renderer *mainRenderer,SDLButtons* button);
void displayGUILevel(SDL_Renderer *mainRenderer, SDLGUI *gui);

void controlHoverButton(SDL_Renderer *mainRenderer, SDLButtons **buttons,unsigned short currentCounterButton, unsigned short sizeArrButton, unsigned short hoverBool);
void controlSelectButton(SDL_Renderer *mainRenderer, SDLButtons **buttons,unsigned short currentCounterButton,unsigned short startCounter, unsigned short sizeArrButton,  unsigned short selectBool);
void updateMenuButtonColor(SDL_Renderer *mainRenderer, SDLButtons* button, SDL_Color buttonColor);

void updateLevelButtonColor(SDL_Renderer *mainRenderer, SDLButtons* button);

short getSelectedMetroLineCounter(SDLContainer *container);
short getSelectedTransportButton(SDLContainer *container);

void buttonEventManagerLevel(SDL_Renderer *mainRenderer, SDL_Point *mousePoint,SDLContainer *rightContainer, SDLContainer *leftContainer, short selectBool );

#endif