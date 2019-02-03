#ifndef TRANSPORT
#define TRANSPORT

#include <stdio.h>

#include <SDLColor.h>
#include <SDLMetroLine.h>
#include <SDLObjectsStructures.h>
#include <SDLBackgroundObjects.h>
#include <mathCalculation.h>
#include <SDLGUIObjects.h>
#include <SDLRectPoint.h>
#include <SDLDraw.h>

#include <SDL.h>


//Fonction gérant les différents événements liés aux actions menées par les utilisateurs sur les éléments de type voiture ou moteur (ajout, suppression)
void transportEventManager(SDL_Renderer *mainRenderer, SDLBackground *background, SDLContainer *leftContainer, SDLContainer *rightContainer, MetroLine ***arrMetroLines , Car ***arrCar, Engine ***arrEngine,int sizeArrMetroLine,unsigned short *sizeArrCar, unsigned short *sizeArrEngine, unsigned short transportSize,  SDL_Point *mousePoint,unsigned short metroLineThickness, short selectBool);


void updateDisplayEngines(SDL_Renderer *mainRenderer, SDLBackground *background,Engine ***arrEngine, MetroLine ***arrMetroLine, MetroStation ***arrMetroStation,unsigned short sizeArrEngine, unsigned short sizeArrMetroLine, int sizeArrMetroStation ,unsigned short metroLineThickness );

//Fonction permettant de créer soit un moteur soit une voiture. 
void createTransport(SDL_Renderer *mainRenderer,Car **car, Engine **engine, MetroLine **metroLine, unsigned short transportSize,unsigned short sizeArrPassenger, TransportType transportType, unsigned short metroLineThickness);

//Fonction permettant de créer un moteur, de lui attribuer une position de départ sur la première station de métro d'une ligne de métro et de déterminer sa direction en fonction de son prochain point de passage. 
void createEngine(SDL_Renderer *mainRenderer,Engine **engine,MetroLine **metroLine, unsigned short transportSize, unsigned short metroLineThickness);

//Fonction permettant de créer une voiture, de l'affecter à un moteur ou de l'affecter à une autre voiture si le moteur en possède déja. Sa position est déterminée en fonction de l'élement auquel elle est rattachée ainsi qu'à la direction de cette élément.
void createCar(Engine **engine,Car **car,MetroLine **metroLine, unsigned short transportSize, unsigned short sizeArrPassenger);


Car *getLastCar(Engine **currentEngine, Car **currentCar, unsigned short *carCounter);

Engine* getLightestEngineOnLine(MetroLine **metroLine, Engine ***arrEngine, unsigned short sizeArrEngine);


#endif 