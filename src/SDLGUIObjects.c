#include <stdio.h>

#include <SDLObjectsStructures.h>
#include <SDLGUIObjects.h>

#include <SDL.h>
#include <SDLDraw.h>
#include <SDLColor.h>
#include <SDL_ttf.h>
#include <SDLRectPoint.h>



//
// ─── FONCTIONS DE GESTION EVENEMENTIELLE ────────────────────────────────────────
//

short controlSelectButton(SDL_Renderer *mainRenderer, SDLButtons **buttons,unsigned short currentCounterButton,unsigned short startCounter, unsigned short sizeArrButton,  unsigned short selectBool){

    
    if(selectBool){
        for(unsigned short counterButton=startCounter; counterButton<sizeArrButton; counterButton++){           
            if(counterButton!=currentCounterButton && buttons[counterButton]->selected && buttons[counterButton]->display && buttons[currentCounterButton]->display){
                buttons[counterButton]->color=SDLChangeRGBColor(255,255,255,255);
                buttons[counterButton]->selected=0;
                buttons[counterButton]->insideColor=buttons[counterButton]->savedColor;
                if(updateLevelButtonColor(mainRenderer,buttons[counterButton])==0){
                    createErrorReport("Echec lors de le la mise à jour de la couleur d'un bouton",__FILE__,__LINE__,__DATE__,__TIME__);
                    return 0;
                }
            }
        }
        if(buttons[currentCounterButton]->selected==0 && buttons[currentCounterButton]->display){
            buttons[currentCounterButton]->selected=1;
            buttons[currentCounterButton]->color=SDLChangeRGBColor(0,0,0,255);
            buttons[currentCounterButton]->insideColor=SDLChangeRGBColor(buttons[currentCounterButton]->insideColor.r+10,buttons[currentCounterButton]->insideColor.g+10,buttons[currentCounterButton]->insideColor.b+10,buttons[currentCounterButton]->insideColor.a);  
            if(updateLevelButtonColor(mainRenderer,buttons[currentCounterButton])==0){
                createErrorReport("Echec lors de le la mise à jour de la couleur d'un bouton",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }
    }
    else{
        for(unsigned short counterButton=startCounter; counterButton<sizeArrButton; counterButton++){
            if(buttons[counterButton]->selected && buttons[counterButton]->display){
                buttons[counterButton]->color=SDLChangeRGBColor(255,255,255,255);
                buttons[counterButton]->selected=0;
                buttons[currentCounterButton]->insideColor=buttons[currentCounterButton]->savedColor;
                if(updateLevelButtonColor(mainRenderer,buttons[counterButton])==0){
                    createErrorReport("Echec lors de le la mise à jour de la couleur d'un bouton",__FILE__,__LINE__,__DATE__,__TIME__);
                    return 0;
                }
            }
        }
    }
    return 1;
}

short getSelectedMetroLineCounter(SDLContainer *container){

    for(int counterButtons=3; counterButtons<container->sizeArrayButtons; counterButtons++){
        if(container->arrayButtons[counterButtons]->selected){
            return counterButtons-3; 
        }
    }
    return -1;
}

short getSelectedTransportButton(SDLContainer *container){

    for(int counterButtons=0; counterButtons<container->sizeArrayButtons; counterButtons++){
        if(container->arrayButtons[counterButtons]->selected){
            return container->arrayButtons[counterButtons]->buttonName;
        }
    }
    return -1;
}

short buttonEventManagerLevel(SDL_Renderer *mainRenderer, SDL_Point *mousePoint,SDLContainer *rightContainer, SDLContainer *leftContainer, short selectBool ){

    for(int counterButton=3; counterButton<rightContainer->sizeArrayButtons; counterButton++){
        if(hasIntersectPointRect(mousePoint,&rightContainer->arrayButtons[counterButton]->rect)){
            if(controlSelectButton(mainRenderer, rightContainer->arrayButtons,counterButton, 3,rightContainer->sizeArrayButtons,selectBool)==0){
                createErrorReport("Echec lors du controle de selection de bouton",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }
    }

    for(int counterButton=0; counterButton<3; counterButton++){
        if(hasIntersectPointRect(mousePoint,&rightContainer->arrayButtons[counterButton]->rect)){
            if(controlSelectButton(mainRenderer, rightContainer->arrayButtons,counterButton, 0,3,1)==0){
                createErrorReport("Echec lors du controle de selection de bouton",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }
    }       
    for(int counterButton=0; counterButton<leftContainer->sizeArrayButtons; counterButton++){
        if(hasIntersectPointRect(mousePoint,&leftContainer->arrayButtons[counterButton]->rect)){
            if(controlSelectButton(mainRenderer, leftContainer->arrayButtons,counterButton, 0,leftContainer->sizeArrayButtons,selectBool)==0){
                createErrorReport("Echec lors du controle de selection de bouton",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }
    }
    return 1;
}

        
//
// ─── FONCTION D'AFFICHAGE ────────────────────────────────────────────────────────
//


short displayTextButton(SDL_Renderer *mainRenderer, SDLButtons* buttonHostMenu){

    int wText;
    int hText;

    if((buttonHostMenu->text->font=TTF_OpenFont(buttonHostMenu->text->fontPath,buttonHostMenu->text->sizeFont))==NULL){
        fprintf(stderr,"Echec lors de l'ouverture de la police dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,TTF_GetError());
        return 0;
    }
    if((buttonHostMenu->text->surface=TTF_RenderText_Blended(buttonHostMenu->text->font,buttonHostMenu->text->content,buttonHostMenu->text->color))==NULL){
        fprintf(stderr,"Echec lors la creation la création de la surface de texte dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,TTF_GetError());
        return 0;
    }
    if((buttonHostMenu->text->texture=SDL_CreateTextureFromSurface(mainRenderer,buttonHostMenu->text->surface))==NULL){
        fprintf(stderr,"Echec lors la creation de la texture dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }
    SDL_FreeSurface(buttonHostMenu->text->surface);

    if(SDL_QueryTexture(buttonHostMenu->text->texture, NULL, NULL, &buttonHostMenu->text->rect.w, &buttonHostMenu->text->rect.h)!=0){
        fprintf(stderr,"Echec lors du la récupération des attributs de la texture dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }
    if(TTF_SizeText(buttonHostMenu->text->font,buttonHostMenu->text->content,&wText,&hText)!=0){
        fprintf(stderr,"Echec lors de la récupération de la taille de police dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,TTF_GetError());
        return 0;
    }

    buttonHostMenu->text->rect.x=buttonHostMenu->rect.x+buttonHostMenu->rect.w/2 - wText/2;
    buttonHostMenu->text->rect.y=buttonHostMenu->rect.y+buttonHostMenu->rect.h/2 - hText/2;

    if(SDL_RenderCopy(mainRenderer,buttonHostMenu->text->texture,NULL,&buttonHostMenu->text->rect)!=0){
        fprintf(stderr,"Echec lors de la copie de texture dans le rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }
    return 1;
}


short displayContainer(SDL_Renderer *mainRenderer,SDLContainer *container){

    
    if((container->texture=SDL_CreateTexture(mainRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,container->rect.w,container->rect.h))==NULL){
        fprintf(stderr,"Echec lors la creation de la texture dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }

    if(SDL_SetTextureBlendMode(container->texture,SDL_BLENDMODE_BLEND)!=0){
        fprintf(stderr,"Echec lors dde la mise en place du blend mode sur la texture dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }
    if(SDL_SetRenderTarget(mainRenderer, container->texture)!=0){
        fprintf(stderr,"Echec lors du ciblage de la texture par le renderer dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }
    if(SDL_SetRenderDrawColor(mainRenderer,container->color.r,container->color.g,container->color.b,container->color.a)!=0){
        fprintf(stderr,"Echec lors du reglage de la couleur de rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }

    if(SDL_RenderFillRect(mainRenderer,NULL)!=0){
        fprintf(stderr,"Echec lors du remplissage de la texture par le renderer dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }
    if(SDL_SetRenderTarget(mainRenderer, NULL)!=0){
        fprintf(stderr,"Echec lors du deciblage de la texture par le renderer dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }
    if(SDL_RenderCopy(mainRenderer,container->texture,NULL,&container->rect)!=0){
        fprintf(stderr,"Echec lors de la copie de texture dans le rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }
    SDL_RenderPresent(mainRenderer);

    return 1;
}


short displayRectButton(SDL_Renderer *mainRenderer,SDLButtons* button){

    if((button->texture=SDL_CreateTexture(mainRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,button->rect.w,button->rect.h))==NULL){
        fprintf(stderr,"Echec lors la creation de la texture dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }

    if(SDL_SetRenderTarget(mainRenderer,button->texture)!=0){
        fprintf(stderr,"Echec lors du ciblage de la texture par le renderer dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }

    if(SDL_SetRenderDrawColor(mainRenderer,button->color.r, button->color.g, button->color.b, button->color.a )!=0){
        fprintf(stderr,"Echec lors du reglage de la couleur de rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }
    if(SDL_RenderClear(mainRenderer)!=0){
        fprintf(stderr,"Echec lors du remplissage du renderer par la couleur de rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }

    if(SDL_SetRenderTarget(mainRenderer,NULL)!=0){
        fprintf(stderr,"Echec lors du ciblage de la texture par le renderer dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }
    if(SDL_RenderCopy(mainRenderer,button->texture,NULL,&button->rect)!=0){
        fprintf(stderr,"Echec lors de la copie de texture dans le rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }

    return 1;
}  


short displayButtonInCircle(SDL_Renderer *mainRenderer,SDLButtons* button){

    if(button->backgroundSurface==NULL){
        button->backgroundSurface=SDL_CreateRGBSurfaceWithFormat(0,button->rect.w,button->rect.h,32,SDL_PIXELFORMAT_RGBA8888);
    }
    
    if(drawGeometricShapeInGeometricShape(
        button->backgroundSurface,&button->rect,  
        SDL_MapRGBA(button->backgroundSurface->format,button->color.r,button->color.g,button->color.b,button->color.a),
        SDL_MapRGBA(button->backgroundSurface->format,button->insideColor.r,button->insideColor.g,button->insideColor.b,button->insideColor.a),_CIRCLE_, 6,0)==0){
            createErrorReport("Echec lors de la création d'une forme géométrique vide",__FILE__,__LINE__,__DATE__,__TIME__);
            return 0;
    }

    if(button->surface!=NULL){
        if((button->texture=SDL_CreateTextureFromSurface(mainRenderer,button->surface))==NULL){
            return 0;
            fprintf(stderr,"Echec lors la creation de la texture dans le fichier %s ligne %d (%s)\n",__FILE__,__LINE__,SDL_GetError());
        }
    }
    if(SDL_SetRenderTarget(mainRenderer,NULL)!=0){
        fprintf(stderr,"Echec lors du ciblage de la texture par le renderer dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }
    if(button->backgroundSurface!=NULL){
        if((button->backgroundTexture=SDL_CreateTextureFromSurface(mainRenderer,button->backgroundSurface))==NULL){
            fprintf(stderr,"Echec lors de la convertion de surface en texture dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
            return 0;
        }
    }

    if(button->backgroundTexture!=NULL){
        if(SDL_RenderCopy(mainRenderer,button->backgroundTexture,NULL,&button->rect)!=0){
        fprintf(stderr,"Echec lors de la copie de texture dans le rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
        }
    }

    button->display=1;

    if(button->texture!=NULL){
        if(SDL_RenderCopy(mainRenderer,button->texture,NULL,&button->rect)!=0){
            fprintf(stderr,"Echec lors de la copie de texture dans le rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
            return 0;
        }                
    }   
    return 1;
}  

short displayGUILevel(SDL_Renderer *mainRenderer, SDLGUI *gui){
    SDLContainer *tmpContainer;

    for(unsigned short counterContainer=0; counterContainer<2; counterContainer++){
        tmpContainer=counterContainer==0?gui->leftContainer:gui->rightContainer;
        if(displayContainer(mainRenderer,tmpContainer)==0){
            createErrorReport("Echec lors de l'affichage d'un conteneur",__FILE__,__LINE__,__DATE__,__TIME__);
            return 0;
        }
         for(unsigned short counterButton=0;counterButton < tmpContainer->sizeArrayButtons ; counterButton ++){
            if(tmpContainer->arrayButtons[counterButton]->display){
                if(displayButtonInCircle(mainRenderer,tmpContainer->arrayButtons[counterButton])==0){
                    createErrorReport("Echec lors de l'affichage d'un bouton circulaire",__FILE__,__LINE__,__DATE__,__TIME__);
                    return 0;
                }
            }
        }
        tmpContainer=NULL;
    }
    return 1;
}


short controlHoverButton(SDL_Renderer *mainRenderer, SDLButtons **buttons,unsigned short currentCounterButton, unsigned short sizeArrButton, unsigned short hoverBool){

    if(hoverBool){
        for(unsigned short counterButton=0; counterButton<sizeArrButton; counterButton++){

            if(counterButton!=currentCounterButton && buttons[counterButton]->hover){

                buttons[counterButton]->hover=0;
                buttons[counterButton]->color=SDLChangeRGBColor(buttons[counterButton]->color.r-10,buttons[counterButton]->color.g-10,buttons[counterButton]->color.b-10,buttons[counterButton]->color.a);
                if(updateMenuButtonColor(mainRenderer,buttons[counterButton],buttons[counterButton]->color)==0){
                    createErrorReport("Echec lors de le la mise à jour de la couleur d'un bouton",__FILE__,__LINE__,__DATE__,__TIME__);
                    return 0;
                }
            }
        }
        if(buttons[currentCounterButton]->hover==0){

            buttons[currentCounterButton]->hover=1;
            buttons[currentCounterButton]->color=SDLChangeRGBColor(buttons[currentCounterButton]->color.r+10,buttons[currentCounterButton]->color.g+10,buttons[currentCounterButton]->color.b+10,buttons[currentCounterButton]->color.a);  
            if(updateMenuButtonColor(mainRenderer,buttons[currentCounterButton],buttons[currentCounterButton]->color)==0){
                createErrorReport("Echec lors de le la mise à jour de la couleur d'un bouton",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }
    }
    else{
        for(unsigned short counterButton=0; counterButton<sizeArrButton; counterButton++){

            if(buttons[counterButton]->hover){
                buttons[counterButton]->hover=0;
                buttons[counterButton]->color=SDLChangeRGBColor(buttons[counterButton]->color.r-10,buttons[counterButton]->color.g-10,buttons[counterButton]->color.b-10,buttons[counterButton]->color.a);
                if(updateMenuButtonColor(mainRenderer,buttons[counterButton],buttons[counterButton]->color)==0){
                    createErrorReport("Echec lors de le la mise à jour de la couleur d'un bouton",__FILE__,__LINE__,__DATE__,__TIME__);
                    return 0;
                }
            }
        }
    }
    return 1;
}


short updateMenuButtonColor(SDL_Renderer *mainRenderer, SDLButtons* button, SDL_Color buttonColor){

    if(button->display){
        button->color=buttonColor;
        if(button->texture!=NULL){
            SDL_DestroyTexture(button->texture);
            button->texture=NULL;
            if(displayRectButton(mainRenderer,button)==0){
                createErrorReport("Echec lors de l'affichage d'un bouton rectangulaire",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }
       
       if(button->text->texture!=NULL){
            SDL_DestroyTexture(button->text->texture);
            button->text->texture=NULL;
            if(displayTextButton(mainRenderer,button)==0){
                createErrorReport("Echec lors de l'affichage de texte dans un bouton",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }       
    }   
    return 1;
}

short updateLevelButtonColor(SDL_Renderer *mainRenderer, SDLButtons* button){

    if(button->display){
        if(button->backgroundTexture!=NULL){
            SDL_DestroyTexture(button->backgroundTexture);
            SDL_DestroyTexture(button->texture);
            SDL_FreeSurface(button->backgroundSurface);
            button->backgroundSurface=NULL;
            button->texture=NULL;
            button->backgroundTexture=NULL;
            if(displayButtonInCircle(mainRenderer,button)==0){
                createErrorReport("Echec lors de l'affichage d'un bouton circulaire",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }     
    }   
    return 1;
}






