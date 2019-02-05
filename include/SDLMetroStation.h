#ifndef METROSTATION
#define METROSTATION

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


//
// ─── FONCTIONS DE GESTION EVENEMENTIELLE ────────────────────────────────────────
//

//Retourne deux stations de métros ayant un statut sélectionné différent de 0
void getSelectedMetroStations(MetroStation **arrMetroStations, MetroStation **srcMetroStation, MetroStation **dstMetroStation, int sizeArrMetroStation);

//Gère le méchanisme de sélection de stations de métro, 3 type de sélection : 
//0 = pas sélectionnée
//1 = sélectionnée en temps que station source pour le tracé d'un segment
//2 = sélectionnée en temps que station destination pour le tracé d'un segment
short controlSelectedMetroStation(SDL_Renderer *mainRenderer, MetroStation **arrayMetroStation,unsigned short currentMetroStation, unsigned short sizeArrMetroStation, unsigned short selectedBool);


//
// ─── FONCTION D'AFFICHAGE ────────────────────────────────────────────────────────
//

//Modifie la couleur des stations de métros si elles sont sélectionnées ou non
short updateColorMetroStation(SDL_Renderer *mainRenderer,MetroStation *metroStation);

//Met à jour l'affichage des stations de métros présentes dans un tableau de station de métro, dans le cas du menu prend en compte l'affichage des boutons et les éventuels chevauchement de ces derniers pour les mettre à jour si chevauchement il y a. 
short updateDisplayMetroStations(SDL_Renderer *mainRenderer, SDLBackground *backgroundMenu,SDLButtons **buttonsHostMenu, unsigned short sizeArrayButtons,MenuLevel menuOrLevel);

//Met à jour l'affichage d'une station de métro en particulier, si sa texture existe déja elle est détruite, sinon elle est crée. Par la suite sa forme géométrique est déssinée, sa texture est copiée dans le rendu puis sa surface est libérée.
short displayMetroStation(SDL_Renderer *mainRenderer, MetroStation *metroStation, SDL_Color *color, SDL_Color *insideColor);


//
// ─── FONCTIONS DE GESTION DE POSITION  ─────────────────────────
//

//Vérifie si le SDL_Rect d'une station de métro présente dans un tableau ne chevauche pas les SDL_Rect d'autres stations de métro présentes dans ce même tableau , si c'est le cas boucle en le modifiant tamps que celui ci chevauche un autre élément
SDL_Rect controlOverlapMetroStations(MetroStation ***arrMetroStations, unsigned short counterMetroStations,SDL_Rect *parentRect,int sizeMetroStation, double sizeFactor);


//
// ─── FONCTIONS DE MANIPULATION DE POINTEURS DE STATIONS DE METRO ──────────────────────────
//

//Effectue un trie par distance du plus proche au plus lointain pour un sous tableau de station de métro, permet ainsi pour chaque station de métro de savoir quelles sont les stations de métros l'entourant de la plus proche à la plus lointaine
void sortArrayMetroStationByDistance(MetroStation **arrMetroStations,unsigned short sizeArrMetroStations);

//Parcour un tableau de station de métro, pour chaque station de métro rempli un sous tableau de station de métro en excluant la station de métro propriétaire du sous tableau
void fillArrayMetroStation(MetroStation **arrMetroStations, unsigned short sizeArrMetroStations);


//
// ─── FONCTIONS DE CREATION DE STATIONS DE METRO ───────────────────────
//

//Créé une station de métro s'assure que la station de métro ne chevauche pas une autre station de métro et s'assure dans le cas d'un niveau que celle ci ne chevauche pas une zone d'eau
short SDLCreateMetroStations(SDLBackground *background, MenuLevel menuOrLevel);



#endif 