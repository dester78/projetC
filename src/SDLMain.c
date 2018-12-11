#include <stdio.h>
#include <stdlib.h>

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



int SDLMainMenuLoop(SDL_Window  *mainWindow, SDL_Renderer *mainRenderer, SDLConfig *SDLConfigElement,DbConfig *dbConfigElement,MYSQL *dbConnection, Files **arrayFiles){

    int windowLoop;
    int sizeArrayButtons=4; 
    int dbConnectionStatus;
    int saveButton=-1;
    int currentTime=0;
    int pastTime=0;
        
    SDLBackground *backgroundHostMenu;
    SDLContainer *containerHostMenu;
    SDLButtons **buttonsHostMenu;
    SDL_Event event;

    SDL_Color saveColor;

    dbConnectionStatus=(mysql_get_host_info(dbConnection)!=NULL);//Status de connexion vaut 1 si fonction retourne une valeur différente à NULL

    // SDL_RenderClear(mainRenderer);
    // SDL_SetRenderDrawColor(mainRenderer,255,255,255,255);
    // SDL_RenderPresent(mainRenderer);
    // SDL_SetRenderTarget(mainRenderer,NULL);
    backgroundHostMenu=malloc(sizeof(SDLBackground));
    containerHostMenu=malloc(sizeof(SDLContainer));
    buttonsHostMenu=malloc(sizeof(SDLButtons*)*sizeArrayButtons);

    for(int counterButton=0; counterButton<sizeArrayButtons; counterButton++){
        
        buttonsHostMenu[counterButton]=malloc(sizeof(SDLButtons));
        buttonsHostMenu[counterButton]->text=malloc(sizeof(SDLText));

    }
    
   
    
    initBackgroundHostMenu(mainWindow,backgroundHostMenu);
    SDLCreateBackgroundHostMenu(mainRenderer,backgroundHostMenu);

    
    initContainerHostMenu(mainWindow,containerHostMenu);
    SDLCreateContainerHostMenu(mainRenderer,containerHostMenu);

    initButtonsHostMenu(mainWindow,containerHostMenu,buttonsHostMenu, SDLConfigElement->ttf->fontMenu, &sizeArrayButtons, dbConnectionStatus);

    for(int counterButton=0; counterButton<sizeArrayButtons; counterButton++){
        
        SDLCreateButton(mainRenderer,buttonsHostMenu[counterButton]);
        SDLCreateTextButton(mainRenderer,buttonsHostMenu[counterButton]);
    }

    while(windowLoop){

        SDL_PollEvent(&event);

        switch(event.type){

            case SDL_QUIT : 
            windowLoop = 0;
            break;

            case SDL_MOUSEMOTION : 

                for(int counterButton=0; counterButton<sizeArrayButtons; counterButton++){

                    if(saveButton == -1){
                        if(event.motion.x >= buttonsHostMenu[counterButton]->rect.x && event.motion.x <= buttonsHostMenu[counterButton]->rect.w+buttonsHostMenu[counterButton]->rect.x && event.motion.y >= buttonsHostMenu[counterButton]->rect.y && event.motion.y <= buttonsHostMenu[counterButton]->rect.h+buttonsHostMenu[counterButton]->rect.y){
   
                            saveButton=counterButton;
                            saveColor=buttonsHostMenu[counterButton]->color;
                            buttonHoverEffect(mainRenderer,buttonsHostMenu[counterButton],SDLChangeRGBColor(buttonsHostMenu[counterButton]->color.r+10,buttonsHostMenu[counterButton]->color.g+10,buttonsHostMenu[counterButton]->color.b+10,255));

                        }
                    }

                    if(saveButton != -1){
                        if(event.motion.x < buttonsHostMenu[saveButton]->rect.x || event.motion.x > buttonsHostMenu[saveButton]->rect.w+buttonsHostMenu[saveButton]->rect.x || event.motion.y < buttonsHostMenu[saveButton]->rect.y || event.motion.y > buttonsHostMenu[saveButton]->rect.h+buttonsHostMenu[saveButton]->rect.y){
                            
                            buttonsHostMenu[saveButton]->color=saveColor;
                            buttonHoverEffect(mainRenderer,buttonsHostMenu[saveButton],buttonsHostMenu[saveButton]->color);
                            saveButton= -1;
                        }  
                    }
                }
            break;


            case SDL_MOUSEBUTTONUP: 

                
                if(event.button.x >= buttonsHostMenu[3]->rect.x && event.button.x <= buttonsHostMenu[3]->rect.w+buttonsHostMenu[3]->rect.x){
                    if(event.button.y >= buttonsHostMenu[3]->rect.y && event.button.y <= buttonsHostMenu[3]->rect.h+buttonsHostMenu[3]->rect.y){
                        event.type=SDL_QUIT;
                    }
                }

                else if(event.button.x >= buttonsHostMenu[2]->rect.x && event.button.x <= buttonsHostMenu[2]->rect.w+buttonsHostMenu[2]->rect.x){
                    if(event.button.y >= buttonsHostMenu[2]->rect.y && event.button.y <= buttonsHostMenu[2]->rect.h+buttonsHostMenu[2]->rect.y){
                        
                        
                    }
                }
            break; 

                     
        }
        SDL_RenderPresent(mainRenderer);

    }


    for(int counterButton=0;counterButton<sizeArrayButtons;counterButton++){
        printf("freeSDLButton\n");
        printf("%d",buttonsHostMenu[counterButton]->text->sizeFont);
        freeSDLButton(buttonsHostMenu[counterButton]);
        
    }   

    
    free(buttonsHostMenu);
    
    return 0;
}



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

//  void SDLAnimateBackgroundHostMenu( SDL_Surface **surface, SDL_Color newColor ){

//     Uint32 *pixels;
//     Uint32 pixelColor;
//     int wSurface;
//     int hSurface;
//     size_t counterHeight,counterWidth;

//     wSurface=(*surface)->w;
//     hSurface=(*surface)->h;
    
//     if(SDL_LockSurface((*surface))!=0){
//         printf("bug");
//     }


//     pixelColor=SDL_MapRGBA((*surface)->format,newColor.r,0,0, newColor.a);

//     pixels = (*surface)->pixels;

//     printf("%d\n",sizeof(pixels));
//     for(counterHeight = 100; counterHeight < (size_t)hSurface-100; counterHeight++){
//         for(counterWidth = 100; counterWidth < (size_t)wSurface-100; counterWidth++){

//             // printf("\n%p",&pixels[counterHeight * (size_t)wSurface + counterWidth]);
//             // SDL_GetRGBA(pixels[counterHeight * (size_t)wSurface + counterWidth],(*surface)->format,&r,&g,&b,&a);
//             // printf("%d\n rouge",r);
//             if(counterHeight%100==0 && counterWidth%1000==0){

//                 printf("OK");
//                 printf(" counterHeight %d \n",counterHeight);
//                 printf("counterWidth %d \n",counterWidth);
//                 drawCircle(&pixels,(int)counterWidth,(int)counterHeight,40,wSurface,hSurface,pixelColor);
//             }
            
            
//             // printf("%d",r);
//         }
//     }

//     drawCircle(&pixels,100,100,40,wSurface,hSurface,pixelColor);

//     printf("%p\n",&pixels[1*wSurface+3]);
   
//     // cercle(pixels,counterWidth,counterHeight,300,1000,h,pixelColor);
    	
//     SDL_UnlockSurface(*surface);
    
// }



void buttonHoverEffect(SDL_Renderer *mainRenderer, SDLButtons* button, SDL_Color buttonColor){

    button->color=buttonColor;
    SDL_DestroyTexture(button->texture);
    SDLCreateButton(mainRenderer,button);
    SDL_DestroyTexture(button->text->texture);
    SDLCreateTextButton(mainRenderer,button); 
}


// void updateBackgroundMenu(SDLBackground *backgroundMenu)