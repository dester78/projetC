#include <stdio.h>

#include <SDLObjectsStructures.h>
#include <SDLGUIObjects.h>

#include <SDL.h>
#include <SDLDraw.h>
#include <SDLColor.h>
#include <SDL_ttf.h>



void displayTextButton(SDL_Renderer *mainRenderer, SDLButtons* buttonHostMenu){

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


void displayContainer(SDL_Renderer *mainRenderer,SDLContainer *container){

    
    if((container->texture=SDL_CreateTexture(mainRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,container->rect.w,container->rect.h))!=NULL){

        if(SDL_SetTextureBlendMode(container->texture,SDL_BLENDMODE_BLEND)==0){
            if(SDL_SetRenderTarget(mainRenderer, container->texture)==0){
                if(SDL_SetRenderDrawColor(mainRenderer,container->color.r,container->color.g,container->color.b,container->color.a)==0){
                    if(SDL_RenderFillRect(mainRenderer,NULL)==0){
                        if(SDL_SetRenderTarget(mainRenderer, NULL)==0){
                            if(SDL_RenderCopy(mainRenderer,container->texture,NULL,&container->rect)==0){
                                SDL_RenderPresent(mainRenderer);
                            }
                            else{fprintf(stderr,"Echec lors de la copie de texture dans le rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
                        } 
                        else{fprintf(stderr,"Echec lors du deciblage de la texture par le renderer dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());}  
                    }      
                    else{fprintf(stderr,"Echec lors du remplissage de la texture par le renderer dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());}          
                } 
                else{fprintf(stderr,"Echec lors du reglage de la couleur de rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
            }
            else{fprintf(stderr,"Echec lors du ciblage de la texture par le renderer dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}
            }
        else{fprintf(stderr,"Echec lors dde la mise en place du blend mode sur la texture dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}
    }
    else{fprintf(stderr,"Echec lors la creation de la texture dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}
}


void displayRectButton(SDL_Renderer *mainRenderer,SDLButtons* button){

    if((button->texture=SDL_CreateTexture(mainRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,button->rect.w,button->rect.h))!=NULL){
        if(SDL_SetRenderTarget(mainRenderer,button->texture)==0){
            if(SDL_SetRenderDrawColor(mainRenderer,button->color.r, button->color.g, button->color.b, button->color.a )==0){
                if(SDL_RenderClear(mainRenderer)==0){
                    if(SDL_SetRenderTarget(mainRenderer,NULL)==0){

                        if(SDL_RenderCopy(mainRenderer,button->texture,NULL,&button->rect)==0){
                            
                        }

                        else{fprintf(stderr,"Echec lors de la copie de texture dans le rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());} 
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


void displayButtonInCircle(SDL_Renderer *mainRenderer,SDLButtons* button){

    if(button->backgroundSurface==NULL){
        button->backgroundSurface=SDL_CreateRGBSurfaceWithFormat(0,button->rect.w,button->rect.h,32,SDL_PIXELFORMAT_RGBA8888);
    }
    
    drawGeometricShapeInGeometricShape(
        button->backgroundSurface,&button->rect,  
        SDL_MapRGBA(button->backgroundSurface->format,button->color.r,button->color.g,button->color.b,button->color.a),
        SDL_MapRGBA(button->backgroundSurface->format,button->insideColor.r,button->insideColor.g,button->insideColor.b,button->insideColor.a),_CIRCLE_, 6,0);

    if(button->surface!=NULL){
        if((button->texture=SDL_CreateTextureFromSurface(mainRenderer,button->surface))!=NULL){

        }
        else{fprintf(stderr,"Echec lors la creation de la texture dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());}
    }
    
    if(SDL_SetRenderTarget(mainRenderer,NULL)==0){

        if(button->backgroundSurface!=NULL){
            button->backgroundTexture=SDL_CreateTextureFromSurface(mainRenderer,button->backgroundSurface);
        }
        if(SDL_RenderCopy(mainRenderer,button->backgroundTexture,NULL,&button->rect)==0){
            button->display=1;
            if(button->texture!=NULL){
                if(SDL_RenderCopy(mainRenderer,button->texture,NULL,&button->rect)==0){
                    
                }
                else{fprintf(stderr,"Echec lors de la copie de texture dans le rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());}                 
            }    
        }           
    }
    else{fprintf(stderr,"Echec lors du ciblage de la texture par le renderer dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());}
}  




void controlHoverButton(SDL_Renderer *mainRenderer, SDLButtons **buttons,unsigned short currentCounterButton, unsigned short sizeArrButton, unsigned short hoverBool){

    if(hoverBool){
        for(unsigned short counterButton=0; counterButton<sizeArrButton; counterButton++){

            if(counterButton!=currentCounterButton && buttons[counterButton]->hover){

                buttons[counterButton]->hover=0;
                buttons[counterButton]->color=SDLChangeRGBColor(buttons[counterButton]->color.r-10,buttons[counterButton]->color.g-10,buttons[counterButton]->color.b-10,buttons[counterButton]->color.a);
                updateMenuButtonColor(mainRenderer,buttons[counterButton],buttons[counterButton]->color);
            }
        }
        if(buttons[currentCounterButton]->hover==0){

            buttons[currentCounterButton]->hover=1;
            buttons[currentCounterButton]->color=SDLChangeRGBColor(buttons[currentCounterButton]->color.r+10,buttons[currentCounterButton]->color.g+10,buttons[currentCounterButton]->color.b+10,buttons[currentCounterButton]->color.a);  
            updateMenuButtonColor(mainRenderer,buttons[currentCounterButton],buttons[currentCounterButton]->color);
        }
    }
    else{
        for(unsigned short counterButton=0; counterButton<sizeArrButton; counterButton++){

            if(buttons[counterButton]->hover){
                buttons[counterButton]->hover=0;
                buttons[counterButton]->color=SDLChangeRGBColor(buttons[counterButton]->color.r-10,buttons[counterButton]->color.g-10,buttons[counterButton]->color.b-10,buttons[counterButton]->color.a);
                updateMenuButtonColor(mainRenderer,buttons[counterButton],buttons[counterButton]->color);
            }
        }
    }
}

void controlSelectButton(SDL_Renderer *mainRenderer, SDLButtons **buttons,unsigned short currentCounterButton,unsigned short startCounter, unsigned short sizeArrButton,  unsigned short selectBool){

    
    if(selectBool){
        for(unsigned short counterButton=startCounter; counterButton<sizeArrButton; counterButton++){           
            if(counterButton!=currentCounterButton && buttons[counterButton]->selected && buttons[counterButton]->display && buttons[currentCounterButton]->display){
                buttons[counterButton]->color=SDLChangeRGBColor(255,255,255,255);
                buttons[counterButton]->selected=0;
                buttons[counterButton]->insideColor=buttons[counterButton]->savedColor;
                updateLevelButtonColor(mainRenderer,buttons[counterButton]);
            }
        }
        if(buttons[currentCounterButton]->selected==0 && buttons[currentCounterButton]->display){
            buttons[currentCounterButton]->selected=1;
            buttons[currentCounterButton]->color=SDLChangeRGBColor(0,0,0,255);
            buttons[currentCounterButton]->insideColor=SDLChangeRGBColor(buttons[currentCounterButton]->insideColor.r+10,buttons[currentCounterButton]->insideColor.g+10,buttons[currentCounterButton]->insideColor.b+10,buttons[currentCounterButton]->insideColor.a);  
            updateLevelButtonColor(mainRenderer,buttons[currentCounterButton]);
        }
    }
    else{
        for(unsigned short counterButton=startCounter; counterButton<sizeArrButton; counterButton++){
            if(buttons[counterButton]->selected && buttons[counterButton]->display){
                buttons[counterButton]->color=SDLChangeRGBColor(255,255,255,255);
                buttons[counterButton]->selected=0;
                buttons[currentCounterButton]->insideColor=buttons[currentCounterButton]->savedColor;
                updateLevelButtonColor(mainRenderer,buttons[counterButton]);
            }
        }
    }
}

void updateMenuButtonColor(SDL_Renderer *mainRenderer, SDLButtons* button, SDL_Color buttonColor){

    if(button->display){
        button->color=buttonColor;
        if(button->texture!=NULL){
            SDL_DestroyTexture(button->texture);
            button->texture=NULL;
            displayRectButton(mainRenderer,button);
        }
       
       if(button->text->texture!=NULL){
            SDL_DestroyTexture(button->text->texture);
            button->text->texture=NULL;
            displayTextButton(mainRenderer,button); 
        }       
    }   
}

void updateLevelButtonColor(SDL_Renderer *mainRenderer, SDLButtons* button){

    if(button->display){
        if(button->backgroundTexture!=NULL){
            SDL_DestroyTexture(button->backgroundTexture);
            SDL_DestroyTexture(button->texture);
            SDL_FreeSurface(button->backgroundSurface);
            button->backgroundSurface=NULL;
            button->texture=NULL;
            button->backgroundTexture=NULL;
            displayButtonInCircle(mainRenderer,button);
        }
       
    //    if(button->text->texture!=NULL){
    //         SDL_DestroyTexture(button->text->texture);
    //         button->text->texture=NULL;
    //         displayTextButton(mainRenderer,button); 
    //     }       
    }   
}


void displayGUILevel(SDL_Renderer *mainRenderer, SDLGUI *gui){


    SDLContainer *tmpContainer;

    for(unsigned short counterContainer=0; counterContainer<2; counterContainer++){

        tmpContainer=counterContainer==0?gui->leftContainer:gui->rightContainer;
        printf("containerPointer : %p\n",tmpContainer);
        displayContainer(mainRenderer,tmpContainer);
        printf("okDisplayContainer\n");
         for(unsigned short counterButton=0;counterButton < tmpContainer->sizeArrayButtons ; counterButton ++){
             printf("counterButton : %d\n",counterButton);
            if(tmpContainer->arrayButtons[counterButton]->display){
                displayButtonInCircle(mainRenderer,tmpContainer->arrayButtons[counterButton]);
            }
        }
        printf("okDisplayContainer2\n");
        tmpContainer=NULL;
    }
}
