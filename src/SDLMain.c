#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRIANGLE 3
#define SQUARE 2 
#define CIRCLE 1

#include <structures.h> 
#include <fileManager.h>
#include <SDLConfigStructures.h>
#include <SDLObjectsStructures.h>
#include <SDLObjects.h>
#include <SDLMain.h>
#include <SDLDraw.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <mysql.h>



int SDLMainMenuLoop(SDL_Window  **mainWindow, SDL_Renderer **mainRenderer, SDLConfig *SDLConfigElement,DbConfig *dbConfigElement,MYSQL *dbConnection, Files **arrayFiles){

    short windowLoop;

    unsigned short countMetroStation=0;
    short saveButton=-1;
    unsigned int currentTime=0;
    unsigned int pastTime=0;
        
    SDLBackground *backgroundHostMenu;
    SDLGUI *guiHostMenu;

    SDL_Event event;
    SDL_Color saveColor;

    srand(time(NULL));//Initailisation du générateur de nombre aléatoire    

    backgroundHostMenu=malloc(sizeof(SDLBackground));
    guiHostMenu=malloc(sizeof(SDLGUI));

    initGUIHostMenu(mainWindow,guiHostMenu,SDLConfigElement,dbConnection);    
    initBackgroundHostMenu(mainWindow,&backgroundHostMenu);

    SDLCreateBackgroundHostMenu(mainRenderer,&backgroundHostMenu);
    // SDLCreateContainerHostMenu(mainRenderer,containerHostMenu);Pas nécessaire pour l'instant

    for(int counterButton=0; counterButton<guiHostMenu->container->sizeArrayButtons; counterButton++){
        
        SDLCreateButton(mainRenderer,guiHostMenu->container->arrayButtons[counterButton]);
        SDLCreateTextButton(mainRenderer,guiHostMenu->container->arrayButtons[counterButton]);
    }

    
    while(windowLoop){

        SDL_PollEvent(&event);

        switch(event.type){
            
            case SDL_QUIT : 
            windowLoop = 0;
            break;

            case SDL_MOUSEMOTION : 

                for(int counterButton=0; counterButton<guiHostMenu->container->sizeArrayButtons; counterButton++){

                    if(saveButton == -1){
                        if(event.motion.x >= guiHostMenu->container->arrayButtons[counterButton]->rect.x && event.motion.x <= guiHostMenu->container->arrayButtons[counterButton]->rect.w+guiHostMenu->container->arrayButtons[counterButton]->rect.x && event.motion.y >= guiHostMenu->container->arrayButtons[counterButton]->rect.y && event.motion.y <= guiHostMenu->container->arrayButtons[counterButton]->rect.h+guiHostMenu->container->arrayButtons[counterButton]->rect.y){
   
                            saveButton=counterButton;
                            saveColor=guiHostMenu->container->arrayButtons[counterButton]->color;
                            buttonHoverEffect(mainRenderer,guiHostMenu->container->arrayButtons[counterButton],SDLChangeRGBColor(guiHostMenu->container->arrayButtons[counterButton]->color.r+10,guiHostMenu->container->arrayButtons[counterButton]->color.g+10,guiHostMenu->container->arrayButtons[counterButton]->color.b+10,255));

                        }
                    }

                    if(saveButton != -1){
                        if(event.motion.x < guiHostMenu->container->arrayButtons[saveButton]->rect.x || event.motion.x > guiHostMenu->container->arrayButtons[saveButton]->rect.w+guiHostMenu->container->arrayButtons[saveButton]->rect.x || event.motion.y < guiHostMenu->container->arrayButtons[saveButton]->rect.y || event.motion.y > guiHostMenu->container->arrayButtons[saveButton]->rect.h+guiHostMenu->container->arrayButtons[saveButton]->rect.y){
                            
                            guiHostMenu->container->arrayButtons[saveButton]->color=saveColor;
                            buttonHoverEffect(mainRenderer,guiHostMenu->container->arrayButtons[saveButton],guiHostMenu->container->arrayButtons[saveButton]->color);
                            saveButton= -1;
                        }  
                    }
                }
            break;


            case SDL_MOUSEBUTTONUP: 

                
                if(event.button.x >= guiHostMenu->container->arrayButtons[3]->rect.x && event.button.x <= guiHostMenu->container->arrayButtons[3]->rect.w+guiHostMenu->container->arrayButtons[3]->rect.x){
                    if(event.button.y >= guiHostMenu->container->arrayButtons[3]->rect.y && event.button.y <= guiHostMenu->container->arrayButtons[3]->rect.h+guiHostMenu->container->arrayButtons[3]->rect.y){
                        event.type=SDL_QUIT;
                    }
                }

                else if(event.button.x >= guiHostMenu->container->arrayButtons[2]->rect.x && event.button.x <= guiHostMenu->container->arrayButtons[2]->rect.w+guiHostMenu->container->arrayButtons[2]->rect.x){
                    if(event.button.y >= guiHostMenu->container->arrayButtons[2]->rect.y && event.button.y <= guiHostMenu->container->arrayButtons[2]->rect.h+guiHostMenu->container->arrayButtons[2]->rect.y){
                        
                        
                    }
                }
            break; 
                                              
        }

        currentTime = SDL_GetTicks();
        if (currentTime - pastTime > 20) /* Si 30 ms se sont écoulées depuis le dernier tour de boucle */{
            
            if(countMetroStation<backgroundHostMenu->sizeArrMetroStations){

                countMetroStation++;
                if(updateBackgroundMenu(mainRenderer,&backgroundHostMenu,guiHostMenu->container->arrayButtons,guiHostMenu->container->sizeArrayButtons,countMetroStation)){

                    //  for(int i=0 ; i<4; i++){

                    //     buttonHoverEffect(mainRenderer,guiHostMenu->container->arrayButtons[i],guiHostMenu->container->arrayButtons[i]->color);
                        
                    //  }
                }
                pastTime = currentTime; 
            }
            /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */
        }
        

        SDL_RenderPresent(*mainRenderer);
        

    }


    for(int counterButton=0;counterButton<guiHostMenu->container->sizeArrayButtons;counterButton++){

        freeSDLButton(guiHostMenu->container->arrayButtons[counterButton]);
        
    } 

    for(int counterMetroStations=0;backgroundHostMenu->sizeArrMetroStations; countMetroStation++){

        free(backgroundHostMenu->arrMetroStations[counterMetroStations]);
    }

    free(backgroundHostMenu->arrMetroStations);

    free(guiHostMenu->container->arrayButtons);
    
    return 0;
}



void buttonHoverEffect(SDL_Renderer **mainRenderer, SDLButtons* button, SDL_Color buttonColor){

    button->color=buttonColor;
    SDL_DestroyTexture(button->texture);
    SDLCreateButton(mainRenderer,button);
    SDL_DestroyTexture(button->text->texture);
    SDLCreateTextButton(mainRenderer,button); 
}



short  updateBackgroundMenu(SDL_Renderer **mainRenderer, SDLBackground **backgroundMenu,SDLButtons **buttonsHostMenu, unsigned short sizeArrayButtons ,unsigned short countMetroStation){

    int geometricShape=0;
    unsigned short counterButton=0;

        SDLCreateMetroStationsMenu(backgroundMenu,buttonsHostMenu,sizeArrayButtons,countMetroStation );
        for(unsigned short counterMetroStations=0; counterMetroStations<countMetroStation; counterMetroStations++){

            if(((*backgroundMenu)->arrMetroStations[counterMetroStations]->surface=SDL_CreateRGBSurfaceWithFormat(0, (*backgroundMenu)->arrMetroStations[counterMetroStations]->rect.w,(*backgroundMenu)->arrMetroStations[counterMetroStations]->rect.w, 32, SDL_PIXELFORMAT_RGBA8888))!=NULL){
 
            }
            else{fprintf(stderr,"Echec lors la creation de la surface dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}
  
            switch((*backgroundMenu)->arrMetroStations[counterMetroStations]->geometricShape){

                case 3 : 
                    (*backgroundMenu)->arrMetroStations[counterMetroStations]->triangle.rect.h = drawFillTriangle(
                        &(*backgroundMenu)->arrMetroStations[counterMetroStations]->surface,
                        (*backgroundMenu)->arrMetroStations[counterMetroStations]->triangle.rect.x,
                        (*backgroundMenu)->arrMetroStations[counterMetroStations]->triangle.rect.y,
                        (*backgroundMenu)->arrMetroStations[counterMetroStations]->triangle.rect.w,
                        (*backgroundMenu)->arrMetroStations[counterMetroStations]->color);
                break;

                case 1 : 
                    drawFillCircle(
                        &(*backgroundMenu)->arrMetroStations[counterMetroStations]->surface,
                        (*backgroundMenu)->arrMetroStations[counterMetroStations]->circle.xCenter,
                        (*backgroundMenu)->arrMetroStations[counterMetroStations]->circle.yCenter,
                        (*backgroundMenu)->arrMetroStations[counterMetroStations]->circle.radius,
                        (*backgroundMenu)->arrMetroStations[counterMetroStations]->color
                    );
                break;

                case 2 :
                drawVariableRect(
                        &(*backgroundMenu)->arrMetroStations[counterMetroStations]->surface,
                        (*backgroundMenu)->arrMetroStations[counterMetroStations]->square.rect.x,
                        (*backgroundMenu)->arrMetroStations[counterMetroStations]->square.rect.y,
                        (*backgroundMenu)->arrMetroStations[counterMetroStations]->square.rect.w,
                        (*backgroundMenu)->arrMetroStations[counterMetroStations]->square.rect.w,
                        (*backgroundMenu)->arrMetroStations[counterMetroStations]->color
                    );
                break;
            }
     
            SDL_DestroyTexture((*backgroundMenu)->arrMetroStations[counterMetroStations]->texture);
            
            if((*backgroundMenu)->arrMetroStations[counterMetroStations]->overlapRisk==1){

                for(counterButton=0; counterButton<sizeArrayButtons; counterButton++){

                    if(createOverlapRect(&(buttonsHostMenu[counterButton]->rect),&(*backgroundMenu)->arrMetroStations[counterMetroStations]->rect,&(*backgroundMenu)->arrMetroStations[counterMetroStations]->overlapRect)){

                        drawVariableRect(
                        &(*backgroundMenu)->arrMetroStations[counterMetroStations]->surface,
                        (*backgroundMenu)->arrMetroStations[counterMetroStations]->overlapRect.x,
                        (*backgroundMenu)->arrMetroStations[counterMetroStations]->overlapRect.y,
                        (*backgroundMenu)->arrMetroStations[counterMetroStations]->overlapRect.w,
                        (*backgroundMenu)->arrMetroStations[counterMetroStations]->overlapRect.h,
                        SDL_MapRGBA((*backgroundMenu)->surface->format,255,0,0,0)
                        );
                    } 
                }  
            }
            
            (*backgroundMenu)->arrMetroStations[counterMetroStations]->texture=SDL_CreateTextureFromSurface((*mainRenderer),(*backgroundMenu)->arrMetroStations[counterMetroStations]->surface);

            if(SDL_RenderCopy((*mainRenderer),(*backgroundMenu)->arrMetroStations[counterMetroStations]->texture,NULL,&(*backgroundMenu)->arrMetroStations[counterMetroStations]->rect)==0){
                
                SDL_FreeSurface((*backgroundMenu)->arrMetroStations[counterMetroStations]->surface); 
                
            }
        }

    return (short)1;
}


int randInRange(int lowerValue, int higherValue){

    return rand()%(higherValue-lowerValue)+lowerValue;

}




// void drawVariableRect(SDL_Surface **surface, int xRect,int yRect,int wRect,int hRect, Uint32 colorRect){

//     SDL_Rect rect;

//     rect.x = xRect;
//     rect.y = yRect;
//     rect.w = wRect;
//     rect.h = hRect;

//     SDL_FillRect(*surface, &rect, colorRect);
// }





// void drawCircle(Uint32 **pixels,int xCenter, int yCenter, int radius,int wSurface, int hSurface, Uint32 pixelColor){

//   int diameter, y, x;

 
//   diameter = 3 - (2 * radius);
//   x = 0;
//   y = radius;

//   while (y >= x) {
    
    
//     controlPixelPosition(&(*pixels)[(xCenter + x) * wSurface + (yCenter + y)],xCenter + x, yCenter + y,wSurface,hSurface, pixelColor);//Premier quart de cercle
//     controlPixelPosition(&(*pixels)[(xCenter + y) * wSurface + (yCenter + x)],xCenter + y, yCenter + x,wSurface,hSurface, pixelColor);
//     controlPixelPosition(&(*pixels)[(xCenter - x) * wSurface + (yCenter + y)],xCenter - x, yCenter + y,wSurface,hSurface, pixelColor);//Deuxième quart de cercle
//     controlPixelPosition(&(*pixels)[(xCenter - y) * wSurface + (yCenter + x)],xCenter - y, yCenter + x,wSurface,hSurface, pixelColor);
//     controlPixelPosition(&(*pixels)[(xCenter + x) * wSurface + (yCenter - y)],xCenter + x, yCenter - y,wSurface,hSurface, pixelColor);//Troisième quart de cercle
//     controlPixelPosition(&(*pixels)[(xCenter + y) * wSurface + (yCenter - x)],xCenter + y, yCenter - x,wSurface,hSurface, pixelColor);
//     controlPixelPosition(&(*pixels)[(xCenter - x) * wSurface + (yCenter - y)],xCenter - x, yCenter - y,wSurface,hSurface, pixelColor);//Quatrième quart de cercle
//     controlPixelPosition(&(*pixels)[(xCenter - y) * wSurface + (yCenter - x)],xCenter - y, yCenter - x,wSurface,hSurface, pixelColor);
 
//     if (diameter < 0)
//       diameter = diameter + (4 * x) + 6;
//     else {
//       diameter = diameter + 4 * (x - y) + 10;
//       y--;
//     }
//     x++;
//   }
// }








// int parameterMenuLoop(SDL_Renderer *mainRenderer, SDLButtons* button, SDL_Color buttonColor)


// int SDLGetArrayDisplayModes(SDL_DisplayMode **arrayDisplayModes){

//     int modeNumber = SDL_GetNumDisplayModes(0);//Récupère le nombre de mode d'affichage disponibles sur l'écran principal de l'utilisateur 0 (écran principal)

//     if (modeNumber < 0){

//         fprintf(stderr,"Echec lors de la recuperation du nombre de modes (%s)\n",SDL_GetError());
//     }

//     else{

//         if((*arrayDisplayModes=malloc(sizeof(SDL_DisplayMode*)*modeNumber))!=NULL){

//             for (int modeCounter= 0 ; modeCounter < modeNumber ; modeCounter++){

//                 if (SDL_GetDisplayMode(0, modeCounter, ((*arrayDisplayModes)+modeCounter))< 0){//Affectation des modes d'affichage au tableau de modes d'affichage
                    
//                     fprintf(stderr, "Echec lors de la recuperation du mode d'affichage (%s)\n", SDL_GetError());
//                     return 0;
//                 }
//             }  
//              return modeNumber;
//         }
//         else{
//             createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
//         } 
//     }

//     return 0;
// }


// void changeButtonsParameterMenu(SDL_Renderer *mainRenderer, SDLButtons* button, SDL_Color buttonColor)


// Uint32 SDLPixelColor(int r, int g, int b, int a){

//    return r << 24 | g << 16 | b << 8 | a;
// }

// void SDLPixelControl(int x, int y, Uint32 coul)
// {
//   if (x >= 0 && x < affichage->w &&
//       y >= 0 && y < affichage->h)
      
//     setPixel(x, y, coul);
// }




