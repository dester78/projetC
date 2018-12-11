#include <stdio.h>

#include <SDLObjectsStructures.h>
#include <SDLConfigStructures.h>
#include <SDLObjects.h>
#include <SDLMain.h>

#include <SDL.h>
#include <SDL_ttf.h>



SDL_Window* SDLCreateMainWindow(SDLWindowConfig *windowConfigElement){

    SDL_Window  *mainWindow;
    SDL_DisplayMode currentDisplayMode;

    if(windowConfigElement->windowHeight>0&&windowConfigElement->windowWidth>0){
        if( (mainWindow = SDL_CreateWindow("PopTube",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,windowConfigElement->windowWidth,windowConfigElement->windowHeight,windowConfigElement->windowFlag))!=NULL){    
            return mainWindow;
        }
        else{
            fprintf(stderr,"Erreur de creation de la fenetre: %s\n",SDL_GetError());
            return NULL;
        }
    }

    else{
        if(SDL_GetCurrentDisplayMode(0,&currentDisplayMode)==0){
            if( (mainWindow = SDL_CreateWindow("PopTube",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,currentDisplayMode.w,currentDisplayMode.h,windowConfigElement->windowFlag))!=NULL){   
                return mainWindow;
            }
            else{
                fprintf(stderr,"Erreur de creation de la fenetre: %s\n",SDL_GetError());
                return NULL;
            }
        }
        else{
            fprintf(stderr,"Erreur lors du chargement des modes d'affichage");
            return NULL;
        }
    }
}

SDL_Renderer* SDLCreateMainRenderer(SDL_Window *mainWindow, long int rendererFlag){

    SDL_Renderer  *mainRenderer;

    if((mainRenderer=SDL_CreateRenderer(mainWindow,-1,rendererFlag))!=NULL){    
        return mainRenderer;
    }

    else{
        fprintf(stderr,"Erreur de mise en place de moteur de rendu : %s\n",SDL_GetError());
        return NULL;
    }
}



void SDLCreateBackgroundHostMenu(SDL_Renderer *mainRenderer, SDLBackground *background){

    
    if((background->surface=SDL_CreateRGBSurfaceWithFormat(0, background->rect.w,background->rect.h, 32, SDL_PIXELFORMAT_RGBA8888))!=NULL){

        if((SDL_FillRect(background->surface,&background->rect,SDL_MapRGBA(background->surface->format,255,255,255,255)))==0){
            // SDLAnimateBackgroundHostMenu( &background->surface, background->color ); 
            if((background->texture=SDL_CreateTextureFromSurface(mainRenderer,background->surface))!=NULL){

                if(SDL_RenderCopy(mainRenderer,background->texture,NULL,&background->rect)==0){
                    SDL_RenderPresent(mainRenderer);
                }
                else{fprintf(stderr,"Echec lors de la copie de texture dans le rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
            }
            else{fprintf(stderr,"Echec lors de la convertion de la surface en texture dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
        }
        else{fprintf(stderr,"Echec lors du remplissage de la surface par un rectangle dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
    }
    else{fprintf(stderr,"Echec lors la creation de la surface dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}
}


// void SDLCreateBackgroundHostMenu(SDL_Renderer *mainRenderer, SDLBackground *background){

//     if((background->texture=SDL_CreateTexture(mainRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,background->rect.w,background->rect.h))!=NULL){
        
//         if(SDL_SetRenderTarget(mainRenderer, background->texture)==0){
//             if(SDL_SetRenderDrawColor(mainRenderer,background->color.r,background->color.g,background->color.b,background->color.a)==0){
//                 if(SDL_RenderClear(mainRenderer)==0){
//                     if(SDL_SetRenderTarget(mainRenderer, NULL)==0){
//                         if(SDL_QueryTexture(background->texture, NULL, NULL, &background->rect.w, &background->rect.h)==0){

//                             if(SDL_RenderCopy(mainRenderer,background->texture,NULL,&background->rect)==0){
//                                 SDL_RenderPresent(mainRenderer);
//                             }
//                             else{fprintf(stderr,"Echec lors de la copie de texture dans le rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
//                         }
//                         else{fprintf(stderr,"Echec lors du la récupération des attributs de la texture dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
//                     } 
//                     else{fprintf(stderr,"Echec lors du deciblage de la texture par le renderer dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());}
//                 }
//                 else{fprintf(stderr,"Echec lors du remplissage du renderer par la couleur de rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());}
//             } 
//             else{fprintf(stderr,"Echec lors du reglage de la couleur de rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
//         }
//         else{fprintf(stderr,"Echec lors du ciblage de la texture par le renderer dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}
//     }
//     else{fprintf(stderr,"Echec lors la creation de la texture dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}
// }


// void SDLUpdateBackgroundHostMenu(SDLBackground *background){

//     SDL_LockSurface(background);   
     
    

// }

void SDLCreateTextButton(SDL_Renderer *mainRenderer, SDLButtons* buttonHostMenu){

    int wText;
    int hText;

    //Règle le placement vertical des boutons en fonction de l'affichage la fenêtre

    if((buttonHostMenu->text->font=TTF_OpenFont(buttonHostMenu->text->fontPath,buttonHostMenu->text->sizeFont))!=NULL){
        if((buttonHostMenu->text->surface=TTF_RenderText_Blended(buttonHostMenu->text->font,buttonHostMenu->text->content,buttonHostMenu->text->color))!=NULL){
            if((buttonHostMenu->text->texture=SDL_CreateTextureFromSurface(mainRenderer,buttonHostMenu->text->surface))!=NULL){
                SDL_FreeSurface(buttonHostMenu->text->surface);

                if(SDL_QueryTexture(buttonHostMenu->text->texture, NULL, NULL, &buttonHostMenu->text->rect.w, &buttonHostMenu->text->rect.h)==0){
                    if(TTF_SizeText(buttonHostMenu->text->font,buttonHostMenu->text->content,&wText,&hText)==0){
                        buttonHostMenu->text->rect.x=buttonHostMenu->rect.x+buttonHostMenu->rect.w/2 - wText/2;
                        buttonHostMenu->text->rect.y=buttonHostMenu->rect.y+buttonHostMenu->rect.h/2 - hText/2;
                        if(SDL_RenderCopy(mainRenderer,buttonHostMenu->text->texture,NULL,&buttonHostMenu->text->rect)==0){
                            SDL_RenderPresent(mainRenderer);
                        }
                        else{fprintf(stderr,"Echec lors de la copie de texture dans le rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());}
                    }
                    else{fprintf(stderr,"Echec lors de la récupération de la taille de police dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,TTF_GetError());}
                }
                else{fprintf(stderr,"Echec lors du la récupération des attributs de la texture dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
            }
            else{fprintf(stderr,"Echec lors la creation de la texture dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}
        } 
        else{fprintf(stderr,"Echec lors la creation la création de la surface de texte dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,TTF_GetError());}
    }
    else{fprintf(stderr,"Echec lors de l'ouverture de la police dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,TTF_GetError());}
}


void SDLCreateContainerHostMenu(SDL_Renderer *mainRenderer,SDLContainer *containerHostMenu){

    
    if((containerHostMenu->texture=SDL_CreateTexture(mainRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,containerHostMenu->rect.w,containerHostMenu->rect.h))!=NULL){

        // if(SDL_RenderClear(mainRenderer)==0){   
            if(SDL_SetTextureBlendMode(containerHostMenu->texture,SDL_BLENDMODE_BLEND)==0){
                if(SDL_SetRenderTarget(mainRenderer, containerHostMenu->texture)==0){
                    //if(SDL_SetRenderDrawColor(mainRenderer,containerHostMenu->color.r,containerHostMenu->color.g,containerHostMenu->color.b,containerHostMenu->color.a)==0){
                        if(SDL_SetRenderTarget(mainRenderer, NULL)==0){
                            // if(SDL_QueryTexture(containerHostMenu->texture, NULL, NULL, &containerHostMenu->rect.w, &containerHostMenu->rect.h)==0){

                                if(SDL_RenderCopy(mainRenderer,containerHostMenu->texture,NULL,&containerHostMenu->rect)==0){
                                    SDL_RenderPresent(mainRenderer);
                                }
                                else{fprintf(stderr,"Echec lors de la copie de texture dans le rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
                            // }
                            // else{fprintf(stderr,"Echec lors du la récupération des attributs de la texture dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
                        } 
                        else{fprintf(stderr,"Echec lors du deciblage de la texture par le renderer dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());}                   
                    // } 
                    // else{fprintf(stderr,"Echec lors du reglage de la couleur de rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
                }
                else{fprintf(stderr,"Echec lors du ciblage de la texture par le renderer dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}
            }
            else{fprintf(stderr,"Echec lors dde la mise en place du blend mode sur la texture dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}
        // }
        // else{fprintf(stderr,"Echec lors du remplissage du renderer par la couleur de rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());}
    }
    else{fprintf(stderr,"Echec lors la creation de la texture dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}
}


void SDLCreateButton(SDL_Renderer *mainRenderer,SDLButtons* button){

    if((button->texture=SDL_CreateTexture(mainRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,button->rect.w,button->rect.h))!=NULL){
        if(SDL_SetRenderTarget(mainRenderer,button->texture)==0){
            if(SDL_SetRenderDrawColor(mainRenderer,button->color.r, button->color.g, button->color.b, button->color.a )==0){
                if(SDL_RenderClear(mainRenderer)==0){
                    if(SDL_SetRenderTarget(mainRenderer,NULL)==0){
                        if(SDL_QueryTexture(button->texture, NULL, NULL, &button->rect.w, &button->rect.h)==0){

                            if(SDL_RenderCopy(mainRenderer,button->texture,NULL,&button->rect)==0){
                                
                                SDL_RenderPresent(mainRenderer);
                                SDL_SetRenderTarget(mainRenderer,NULL);
                            }

                            else{fprintf(stderr,"Echec lors de la copie de texture dans le rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
                        }
                        else{fprintf(stderr,"Echec lors de la recuperation des attribut de la texture dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
                    }
                    else{fprintf(stderr,"Echec lors du ciblage de la texture par le renderer dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());}
                }
                else{fprintf(stderr,"Echec lors du remplissage du renderer par la couleur de rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());}
            }
            else{fprintf(stderr,"Echec lors du reglage de la couleur de rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
        }
        else{fprintf(stderr,"Echec lors du ciblage de la texture par le renderer dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}
    }
    else{fprintf(stderr,"Echec lors la creation de la texture dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}
}  



