#ifndef SDLGUIOBJECTS
#define SDLGUIOBJECTS

#include <SDLObjectsStructures.h>

#include <SDL.h>


//
// ─── FONCTIONS DE GESTION EVENEMENTIELLE ────────────────────────────────────────
//

//Vérifier si un bouton est sélectionné par la souris de l'utilisateur et le met à jour le cas échéant
short controlSelectButton(SDL_Renderer *mainRenderer, SDLButtons **buttons,unsigned short currentCounterButton,unsigned short startCounter, unsigned short sizeArrButton,  unsigned short selectBool);

//Renvoi l'index d'une ligne de métro sélectionnée dans un tableau de bouton 
short getSelectedMetroLineCounter(SDLContainer *container);

//Renvoi l'index d'un transport sélectionné dans un tableau de bouton
short getSelectedTransportButton(SDLContainer *container);

//Gère les différents événèments liés aux interactions avec les boutons dans un niveau tous conteneurs confondus
short buttonEventManagerLevel(SDL_Renderer *mainRenderer, SDL_Point *mousePoint,SDLContainer *rightContainer, SDLContainer *leftContainer, short selectBool );

//
// ─── FONCTION D'AFFICHAGE ────────────────────────────────────────────────────────
//

//Affiche un texte incrusté dans un bouton
short displayTextButton(SDL_Renderer *mainRenderer, SDLButtons* buttonHostMenu);

//Affiche un conteneur
short displayContainer(SDL_Renderer *mainRenderer,SDLContainer *container);

//Affiche un bouton rectangulaire
short displayRectButton(SDL_Renderer *mainRenderer,SDLButtons* button);

//Affiche un bouton circulaire
short displayButtonInCircle(SDL_Renderer *mainRenderer,SDLButtons* button);

//Affiche une interface utilisateur composée d'un ou plusieurs conteneurs eux mêmes composés d'un ou plusieurs boutons et/ou textes
short displayGUILevel(SDL_Renderer *mainRenderer, SDLGUI *gui);

//Vérifier si un bouton est survolé par la souris de l'utilisateur et le met à jour le cas échéant
short controlHoverButton(SDL_Renderer *mainRenderer, SDLButtons **buttons,unsigned short currentCounterButton, unsigned short sizeArrButton, unsigned short hoverBool);

//Met à jour un bouton et son texte dans le menu
short updateMenuButtonColor(SDL_Renderer *mainRenderer, SDLButtons* button, SDL_Color buttonColor);

//Met à jour un bouton composé d'une texture de fond et du texture normal 
short updateLevelButtonColor(SDL_Renderer *mainRenderer, SDLButtons* button);


#endif