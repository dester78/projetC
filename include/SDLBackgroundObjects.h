#ifndef SDLBACKGROUNDOBJECTS
#define SDLBACKGROUNDOBJECTS

#include <SDLObjectsStructures.h>

#include <SDL.h>


void SDLCreateBackgroundHostMenu(SDL_Renderer *mainRenderer, SDLBackground *background);
void SDLCreateMetroStations(SDLBackground *background, MenuLevel menuOrLevel);
void SDLCreateMetroLineMenu(SDLBackground *backgroundMenu);
void SDLCreateMetroSegmentMenu(SDLBackground *backgroundMenu);


SDL_Rect controlOverlapMetroStations(MetroStation **arrMetroStations, unsigned short counterMetroStations,SDL_Rect *parentRect,int sizeMetroStation, double sizeFactor);


void SDLCreateBackgroundLevel(SDL_Renderer *mainRenderer, SDLBackground *background, SDL_Window *mainWindow);

void sortArrayMetroStationPoints(MetroStation **arrMetroStations,unsigned short sizeArrMetroStations);
void fillArrayMetroStationPoints(MetroStation **arrMetroStations, unsigned short sizeArrMetroStations);

short updateDisplayMetroStations(SDL_Renderer *mainRenderer, SDLBackground *backgroundMenu,SDLButtons **buttonsHostMenu, unsigned short sizeArrayButtons,MenuLevel menuOrLevel);
short updateDisplayMetroLineMenu(SDL_Renderer *mainRenderer, SDLBackground *backgroundMenu,SDLButtons **buttonsHostMenu, unsigned short sizeArrayButtons);
short updateDisplayMetroLineLevel(SDL_Renderer *mainRenderer, MetroLine ***arrMetroLines, MetroStation ***arrMetroStations,int sizeArrMetroLines, int sizeArrMetroStations);

void  updateColorMetroStations(mainRenderer,arrayMetroStation,sizeArrMetroStation);


short displayMetroStation(SDL_Renderer *mainRenderer, MetroStation *metroStation, SDL_Color *color, SDL_Color *insideColor);
short updateDisplayMetroSegment(SDL_Renderer *mainRenderer, MetroSegment *metroSegment, MetroLine *metroLine);

short controlSelectedMetroStation(SDL_Renderer *mainRenderer, MetroStation **arrayMetroStation,unsigned short currentMetroStation, unsigned short sizeArrMetroStation, unsigned short selectedBool);

short getSelectedMetroLineCounter(SDLContainer *container);
void getSelectedMetroStations(MetroStation **arrMetroStations, MetroStation **srcMetroStation, MetroStation **dstMetroStation, int sizeArrMetroStation);

void createMetroSegmentLevel(MetroLine **metroLine, MetroStation **arrMetroStations, int sizeArrMetroStation, short counterMetroLine, short metroLineThickness);


#endif