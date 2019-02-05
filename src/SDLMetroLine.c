
#include <SDLObjectsStructures.h>
#include <SDLRectPoint.h>
#include <SDLMetroLine.h>
#include <SDLMetroStation.h>
#include <fileManager.h>

#include<SDL.h>

//
// ─── FONCTIONS DE GESTION EVENEMENTIELLE ────────────────────────────────────────
//
short metroLineEventManagerLevel(SDL_Renderer *mainRenderer, SDLBackground *background, SDLContainer *container, MetroLine **arrMetroLines , MetroStation **arrMetroStations, Engine ***arrEngine, int sizeArrMetroLine,int sizeArrMetroStations,int sizeArrEngine, unsigned short metroLineThickness, SDL_Point *mousePoint, short selectBool, ContainerPosition containerPosition){

    short metroLineCounter;

    // Récupère les boutons de sélection de ligne sélectionnés dans le conteneur à droite de l'écran.
    if(containerPosition==_RIGHT_){
        metroLineCounter=getSelectedMetroLineCounter(container);

        if((metroLineCounter)!=-1){

            //Control si le clic de la souris porte sur une station de métro et récupère la nature du clic pour appeler la fonction manageMetroSegmentLevel
            for(int counterMetroStation=0; counterMetroStation<sizeArrMetroStations; counterMetroStation++){
                if(hasIntersectPointRect(mousePoint,&arrMetroStations[counterMetroStation]->rect) && arrMetroStations[counterMetroStation]->display){
                    if(controlSelectedMetroStation(mainRenderer, arrMetroStations,counterMetroStation, sizeArrMetroStations,selectBool)==2){    
                        if(manageMetroSegmentLevel(NULL,NULL,&arrMetroLines[metroLineCounter],arrMetroStations,NULL, NULL,sizeArrMetroStations,0,metroLineCounter,metroLineThickness,selectBool)==0){
                            createErrorReport("Echec lors de l'ajout ou suppression d'un segment sur une ligne de metro",__FILE__,__LINE__,__DATE__,__TIME__);
                            return 0;
                        }
                    }
                }
            } 
            //Control si le clic de la souris porte sur un des deux SDL_Rect composant un segment et récupère la nature du clic pour appeler la fonction manageMetroSegmentLevel
            for(int metroSegmentCounter=0; metroSegmentCounter < arrMetroLines[metroLineCounter]->sizeArrSegment; metroSegmentCounter++){

                SDL_Rect absolutePathPointToDstPointRect= absoluteRectPositionInRect(&arrMetroLines[metroLineCounter]->arrMetroSegment[metroSegmentCounter]->pathPointToDstPointRect,&arrMetroLines[metroLineCounter]->arrMetroSegment[metroSegmentCounter]->rect);
                SDL_Rect absoluteSrcPointToPathPointRect= absoluteRectPositionInRect(&arrMetroLines[metroLineCounter]->arrMetroSegment[metroSegmentCounter]->srcPointToPathPointRect,&arrMetroLines[metroLineCounter]->arrMetroSegment[metroSegmentCounter]->rect);
                
                if((hasIntersectPointRect(mousePoint,&absolutePathPointToDstPointRect) || hasIntersectPointRect(mousePoint,&absoluteSrcPointToPathPointRect)) && selectBool==0 ){
                    if(manageMetroSegmentLevel(mainRenderer,background,&arrMetroLines[metroLineCounter],NULL,arrEngine,&arrMetroLines[metroLineCounter]->arrMetroSegment[metroSegmentCounter],0,sizeArrEngine,metroLineCounter,metroLineThickness,selectBool)==0){
                        createErrorReport("Echec lors de l'ajout ou suppression d'un segment sur une ligne de metro",__FILE__,__LINE__,__DATE__,__TIME__);
                        return 0;
                    }  
                }   
            }
        }
    }
    else{
        createErrorReport("Mauvais conteneur donne a la fonction metroLineEventManagerLevel",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;
    }
    return 1;

}

short manageMetroSegmentLevel(SDL_Renderer *mainRenderer, SDLBackground *background, MetroLine **metroLine, MetroStation **arrMetroStations, Engine ***arrEngine, MetroSegment **currentMetroSegment, int sizeArrMetroStation, int sizeArrEngine,short counterMetroLine, short metroLineThickness,short addDeleteBool){

    short addBool=0;
    if(addDeleteBool==1){

        MetroStation *srcMetroStation, *dstMetroStation;
        MetroSegment *newSegment;

        getSelectedMetroStations(arrMetroStations,&srcMetroStation,&dstMetroStation,sizeArrMetroStation);

        if(srcMetroStation==NULL||dstMetroStation==NULL){
            createErrorReport("Pas assez de stations de metro selectionnees pour creer un segment",__FILE__,__LINE__,__DATE__,__TIME__);
            return 0;
        }
        if((newSegment=addNewSegment(&(*metroLine)->arrMetroSegment, &srcMetroStation , &dstMetroStation, &(*metroLine)->sizeArrSegment,&addBool))==NULL){
            createErrorReport("Echec lors de l'ajout d'un segment",__FILE__,__LINE__,__DATE__,__TIME__);
            return 0;
        }
        if(addBool){
            newSegment->surface=NULL;
            newSegment->texture=NULL; 
            createGeometryMetroSegment(newSegment, newSegment->precedentSegment, newSegment->srcStation, newSegment->dstStation, counterMetroLine, metroLineThickness);

        }
            
    } 
    else if(addDeleteBool==0 && *currentMetroSegment!=NULL){
    
        if(controlEngineOnLine(arrEngine,sizeArrEngine,currentMetroSegment)){
            if(deleteSegment(mainRenderer, background,&(*metroLine)->arrMetroSegment, currentMetroSegment,&(*metroLine)->sizeArrSegment)==0){
                createErrorReport("Echec lors de la suppression  d'un segment",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }
    }
    return 1;
}

//
// ─── FONCTION D'AFFICHAGE ────────────────────────────────────────────────────────
//

short updateDisplayMetroLineLevel(SDL_Renderer *mainRenderer, MetroLine ***arrMetroLines, MetroStation ***arrMetroStations,int sizeArrMetroLines, int sizeArrMetroStations){

    for(unsigned short counterMetroLine=0; counterMetroLine<sizeArrMetroLines;counterMetroLine++){

        if((*arrMetroLines)[counterMetroLine]!=0){

            for(unsigned short counterMetroSegment=0; counterMetroSegment<(*arrMetroLines)[counterMetroLine]->sizeArrSegment;counterMetroSegment++){

                //Si les stations de métros raccordées au segment sont affichées on passe à la condition suivante
                if((*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->srcStation->display && (*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->dstStation->display){
                    //Si le segment est seul ou si son segment précédent est affiché et qu'il n'est lui même pas affiché on peut l'afficher
                    if((counterMetroSegment==0 || (*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment-1]->display ) && (*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->display==0 ){

                       if(updateDisplayMetroSegment(mainRenderer, (*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment], (*arrMetroLines)[counterMetroLine])==0){
                            createErrorReport("Echec lors de la mise à jour de l'affichage d'un segment",__FILE__,__LINE__,__DATE__,__TIME__);           
                            return 0;
                       }

                        //Création de SDL_Rect avec une position absolue afin de vérifier les éventuels chevauchement des boutons 
                        SDL_Rect absoluteSrcPointToPathPointRect;
                        SDL_Rect absolutePathPointToDstPointRect;
                        absoluteSrcPointToPathPointRect=absoluteRectPositionInRect(&(*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->srcPointToPathPointRect,&(*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->rect);
                        absolutePathPointToDstPointRect=absoluteRectPositionInRect(&(*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->pathPointToDstPointRect,&(*arrMetroLines)[counterMetroLine]->arrMetroSegment[counterMetroSegment]->rect);

                        for(unsigned short counterMetroStations=0;counterMetroStations< sizeArrMetroStations;counterMetroStations++){
                            //Mise à jour de l'affichage des boutons en cas de par une ligne de métro
                            if(SDL_HasIntersection(&absoluteSrcPointToPathPointRect,&(*arrMetroStations)[counterMetroStations]->rect)||SDL_HasIntersection(&absolutePathPointToDstPointRect,&(*arrMetroStations)[counterMetroStations]->rect)){
                                if(updateColorMetroStation(mainRenderer,(*arrMetroStations)[counterMetroStations])==0){
                                    createErrorReport("Echec lors de la mise à jour de la couleur d'une station",__FILE__,__LINE__,__DATE__,__TIME__);           
                                    return 0;  
                                }
                            }
                        } 

                        break;
                    }
                }         
            }
        }    
    }  

    return 1;
}

short updateDisplayMetroSegment(SDL_Renderer *mainRenderer, MetroSegment *metroSegment, MetroLine *metroLine){

    //Indique que le segment est affiché et indique que les stations ne sont pas affiché pour mise à jour ultérieure
    metroSegment->display=1;
    metroSegment->srcStation->display=0;
    metroSegment->dstStation->display=0;

   if(SDL_SetRenderDrawColor(mainRenderer,metroLine->color.r,metroLine->color.g,metroLine->color.b,metroLine->color.a)!=0){
        fprintf(stderr,"Echec lors du réglage de la couleur de rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
   }

    //Si la texture du segment n'existe pas on la créer et on dessine à l'intérieur sinon on se contente de la copier dans le rendu
    if(metroSegment->texture==NULL){
        metroSegment->texture=SDL_CreateTexture(mainRenderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,metroSegment->rect.w,metroSegment->rect.h);
    }
        if(SDL_SetTextureBlendMode(metroSegment->texture,SDL_BLENDMODE_BLEND)!=0){
            fprintf(stderr,"Echec lors du réglage de la couleur de rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
            return 0;
        }

        if(SDL_SetRenderTarget(mainRenderer,metroSegment->texture)!=0){
            fprintf(stderr,"Echec lors du ciblage de la texture dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
            return 0;
        }
        
        if(SDL_RenderFillRect(mainRenderer,&metroSegment->srcPointToPathPointRect)!=0||SDL_RenderFillRect(mainRenderer,&metroSegment->pathPointToDstPointRect)!=0){
            fprintf(stderr,"Echec lors du remplissage des rectangles dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
            return 0;
        }

        if(SDL_SetRenderDrawColor(mainRenderer,255,255,255,255)!=0){
            fprintf(stderr,"Echec lors du réglage de la couleur de rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
            return 0;
        }
        if(SDL_RenderDrawRect(mainRenderer,&metroSegment->srcPointToPathPointRect)!=0||SDL_RenderDrawRect(mainRenderer,&metroSegment->pathPointToDstPointRect)!=0){
            fprintf(stderr,"Echec lors du coloriage de rectangles dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
            return 0;
        }
        if(SDL_SetRenderTarget(mainRenderer,NULL)!=0){
            fprintf(stderr,"Echec lors du déciblage de la texture dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
            return 0;
        }
    
    if(SDL_RenderCopy(mainRenderer,metroSegment->texture,NULL,&metroSegment->rect)!=0){
        fprintf(stderr,"Echec lors de la copie de la texture dans le rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return 0;
    }

    return 1;
}

short updateDisplayMetroLineMenu(SDL_Renderer *mainRenderer, SDLBackground *backgroundMenu,SDLButtons **buttonsHostMenu, unsigned short sizeArrayButtons){

    for(unsigned short counterMetroLine=0; counterMetroLine<backgroundMenu->sizeArrMetroLines;counterMetroLine++){

        if(backgroundMenu->arrMetroLines[counterMetroLine]!=0){

            for(unsigned short counterMetroSegment=0; counterMetroSegment<backgroundMenu->arrMetroLines[counterMetroLine]->sizeArrSegment;counterMetroSegment++){
                
                if(backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->srcStation->display && backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->dstStation->display){

                    if((counterMetroSegment==0 || backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment-1]->display ) && backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->display==0 ){

                        if(updateDisplayMetroSegment(mainRenderer, backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment], backgroundMenu->arrMetroLines[counterMetroLine])==0){
                            createErrorReport("Echec lors de la mise a jour de l'affichage d'un segment",__FILE__,__LINE__,__DATE__,__TIME__);
                            return 0;
                        }

                        SDL_Rect absoluteSrcPointToPathPointRect;
                        SDL_Rect absolutePathPointToDstPointRect;

                        absoluteSrcPointToPathPointRect=absoluteRectPositionInRect(&backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->srcPointToPathPointRect,&backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->rect);
                        absolutePathPointToDstPointRect=absoluteRectPositionInRect(&backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->pathPointToDstPointRect,&backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->rect);

                        for(unsigned short counterButton=0; counterButton<sizeArrayButtons; counterButton++){

                            if(SDL_HasIntersection(&absoluteSrcPointToPathPointRect,&buttonsHostMenu[counterButton]->rect) || SDL_HasIntersection(&absolutePathPointToDstPointRect,&buttonsHostMenu[counterButton]->rect) ){
                                // controlHoverButton(mainRenderer,buttonsHostMenu,counterButton,sizeArrayButtons);
                                if(updateMenuButtonColor(mainRenderer, buttonsHostMenu[counterButton],  buttonsHostMenu[counterButton]->color)==0){
                                    createErrorReport("Echec lors du changement de couleur d'un bouton",__FILE__,__LINE__,__DATE__,__TIME__);
                                    return 0;
                                }

                            }
                        } 

                        for(unsigned short counterMetroStations=0;counterMetroStations< backgroundMenu->sizeArrMetroStations;counterMetroStations++){
                            
                            if(SDL_HasIntersection(&absoluteSrcPointToPathPointRect,&backgroundMenu->arrMetroStations[counterMetroStations]->rect)||SDL_HasIntersection(&absolutePathPointToDstPointRect,&backgroundMenu->arrMetroStations[counterMetroStations]->rect)){
                                if(displayMetroStation(mainRenderer,backgroundMenu->arrMetroStations[counterMetroStations],&backgroundMenu->arrMetroStations[counterMetroStations]->color,&backgroundMenu->arrMetroStations[counterMetroStations]->insideColor)==0){
                                    createErrorReport("Echec lors de la mise à jour de l'affichage d'une station",__FILE__,__LINE__,__DATE__,__TIME__);
                                    return 0;  
                                }
                                backgroundMenu->arrMetroStations[counterMetroStations]->display=0;
                            }
                        } 
                        break;
                    }
                }         
            }
        }    
    }  
    return 1;
}

//
// ─── FONCTIONS DE GESTION DE POSITION  ─────────────────────────
//
void preparePathRectMetroSegment(MetroSegment *currentMetroSegment, MetroSegment *precedentMetroSegment, unsigned short thickness, unsigned short counterMetroLine){

    currentMetroSegment->pathPointInRect.x=currentMetroSegment->srcPointInRect.x;
    currentMetroSegment->pathPointInRect.y=currentMetroSegment->dstPointInRect.y;

    if(precedentMetroSegment!=NULL){

        avoidOverlapPathPointMetroSegment(
            &currentMetroSegment->pathPointInRect,
            &currentMetroSegment->rect,
            &precedentMetroSegment->pathPointInRect,
            &precedentMetroSegment->rect);      
    }

    placePointPositionInMiddleMetroStation(&currentMetroSegment->pathPointInRect,&currentMetroSegment->srcPointInRect, &currentMetroSegment->rect, &currentMetroSegment->srcStation->rect,currentMetroSegment->srcStation->geometricShape);
    placePointPositionInMiddleMetroStation(&currentMetroSegment->pathPointInRect,&currentMetroSegment->dstPointInRect, &currentMetroSegment->rect, &currentMetroSegment->dstStation->rect,currentMetroSegment->srcStation->geometricShape);

    setThicknessMetroSegmentRect(
    &currentMetroSegment->pathPointInRect,   
    &currentMetroSegment->srcPointInRect,
    &currentMetroSegment->rect,
    &currentMetroSegment->srcPointToPathPointRect,
    thickness, counterMetroLine);

    setThicknessMetroSegmentRect(
    &currentMetroSegment->pathPointInRect,
    &currentMetroSegment->dstPointInRect,
    &currentMetroSegment->rect,
    &currentMetroSegment->pathPointToDstPointRect,
    thickness, counterMetroLine);  
}

void shiftPointPositionMetroLine(SDL_Rect *parentRect, SDL_Point *point, unsigned short counterMetroLine, unsigned short thickness){

    if(point->x==parentRect->w){
        point->x -= thickness * (counterMetroLine+1);
    }
    else{
        point->x += thickness * (counterMetroLine+1);
    }

    if(point->y==parentRect->h){
        point->y -= thickness * (counterMetroLine+1);
    }
    else{
        point->y += thickness * (counterMetroLine+1);
    }
}

void setThicknessMetroSegmentRect(SDL_Point *srcPoint , SDL_Point *dstPoint, SDL_Rect *parentRect, SDL_Rect *finalRect ,unsigned short thickness,unsigned short counterMetroLine){

    SDL_Point tmpSrcPoint , tmpDstPoint;
    tmpSrcPoint = *srcPoint;
                         
    tmpDstPoint = *dstPoint;
            
    if(tmpSrcPoint.y==parentRect->h-(counterMetroLine+1)*thickness && tmpSrcPoint.y==tmpDstPoint.y){
        tmpSrcPoint.y-= thickness;
    }
    else if(tmpSrcPoint.y!=parentRect->h-(counterMetroLine+1)*thickness && tmpSrcPoint.y==tmpDstPoint.y) {
        tmpSrcPoint.y += thickness;
    }

    if(tmpSrcPoint.x==parentRect->w-(counterMetroLine+1)*thickness && tmpSrcPoint.x==tmpDstPoint.x){
        tmpSrcPoint.x-= thickness;
    }
    else if(tmpSrcPoint.x!=parentRect->w-(counterMetroLine+1)*thickness && tmpSrcPoint.x==tmpDstPoint.x) {
        tmpSrcPoint.x += thickness;
    }

    createRectBetweenTwoPoint(&tmpDstPoint,&tmpSrcPoint,finalRect,NULL,NULL);
}

void avoidOverlapPathPointMetroSegment(SDL_Point *currentPathPoint, SDL_Rect *currentRect, SDL_Point *precedentPathPoint, SDL_Rect *precedentRect){

    SDL_Point tmpCurrentPathPoint, tmpPrecedentPathPoint;
    
    tmpCurrentPathPoint=absolutePointPositionInRect(currentPathPoint,currentRect);
    tmpPrecedentPathPoint=absolutePointPositionInRect(precedentPathPoint,precedentRect);

    if(tmpCurrentPathPoint.x==tmpPrecedentPathPoint.x && tmpCurrentPathPoint.y==tmpPrecedentPathPoint.y){

        currentPathPoint->x = currentPathPoint->x==0 ? currentRect->w : 0; 
        currentPathPoint->y = currentPathPoint->y==0 ? currentRect->h : 0; 
    }
}

void placePointPositionInMiddleMetroStation(SDL_Point *srcPoint, SDL_Point *dstPoint, SDL_Rect *parentRect, SDL_Rect *dstRect, GeometricShape geometricShape){

    SDL_Rect tmpRelativeRect; 

    tmpRelativeRect=relativeRectPositionInRect(dstRect,parentRect);

    if(dstPoint->x==srcPoint->x){
        if(geometricShape==_TRIANGLE_){       
            dstPoint->y=tmpRelativeRect.y+tmpRelativeRect.h;
        }
        else{
            dstPoint->y=tmpRelativeRect.y+tmpRelativeRect.h/2;
        }
    }

    else{
        dstPoint->x=tmpRelativeRect.x+tmpRelativeRect.w/2;
    }
}

void createGeometryMetroSegment(MetroSegment *currentMetroSegment, MetroSegment *precedentMetroSegment, MetroStation * srcStation, MetroStation *dstStation, short counterMetroLine, short metroLineThickness){

    currentMetroSegment->srcStation=srcStation;
    currentMetroSegment->dstStation=dstStation;

    createRectBetweenTwoRect(
       &currentMetroSegment->srcStation->rect,&currentMetroSegment->dstStation->rect,&currentMetroSegment->rect,&currentMetroSegment->srcPointInRect,&currentMetroSegment->dstPointInRect);

   currentMetroSegment->display=0;

    shiftPointPositionMetroLine(&currentMetroSegment->rect,&currentMetroSegment->srcPointInRect, counterMetroLine,metroLineThickness);

    shiftPointPositionMetroLine(&currentMetroSegment->rect,&currentMetroSegment->dstPointInRect, counterMetroLine,metroLineThickness);


    if(precedentMetroSegment!=NULL){
        preparePathRectMetroSegment(currentMetroSegment, precedentMetroSegment,metroLineThickness, counterMetroLine);
    }
    else{
        preparePathRectMetroSegment(currentMetroSegment, NULL,metroLineThickness,counterMetroLine);
    }
}


//
// ─── FONCTIONS DE MANIPULATION DE POINTEURS DE SEGMENT ──────────────────────────
//

void reorderMetroSegmentsLastToFirst(MetroSegment ***arrMetroSegment, unsigned short sizeArrSegment){

    MetroSegment *tmpSegment;
 
    tmpSegment=(*arrMetroSegment)[sizeArrSegment-1];

    for(unsigned short counterSegment = sizeArrSegment-1 ; counterSegment >0 ; counterSegment --){
        (*arrMetroSegment)[counterSegment]=(*arrMetroSegment)[(counterSegment-1)];
    }
    (*arrMetroSegment)[0]=tmpSegment;
}

void reorderSrcAndDestStations(MetroSegment **currentMetroSegment, MetroStation **srcMetroStation, MetroStation **dstMetroStation, unsigned short order){


    switch (order){


        case 0:
            (*currentMetroSegment)->srcStation=*srcMetroStation;
            (*currentMetroSegment)->dstStation=*dstMetroStation;
        break;

        case 1:            
            if((*currentMetroSegment)->nextSegment->srcStation==*dstMetroStation){
                (*currentMetroSegment)->srcStation=*srcMetroStation;
                (*currentMetroSegment)->dstStation=(*currentMetroSegment)->nextSegment->srcStation;
            }
            else if((*currentMetroSegment)->nextSegment->srcStation==*srcMetroStation){
                (*currentMetroSegment)->dstStation=(*currentMetroSegment)->nextSegment->srcStation;
                (*currentMetroSegment)->srcStation=*dstMetroStation;          
            }
        break;

        case 2:
            if((*currentMetroSegment)->precedentSegment->dstStation==*srcMetroStation){
                    (*currentMetroSegment)->srcStation=*srcMetroStation;
                    (*currentMetroSegment)->dstStation=*dstMetroStation;
            }
            else if((*currentMetroSegment)->precedentSegment->dstStation==*dstMetroStation){
                (*currentMetroSegment)->srcStation=*dstMetroStation;
                (*currentMetroSegment)->dstStation=*srcMetroStation;          
            }
        break;
    }
}

void linkMetroSegmentMetroStation(MetroStation *metroStation, MetroSegment *metroSegment, unsigned short srcDstBool){

    if(srcDstBool){
        metroSegment->srcStation=metroStation;
    }
    else{
        metroSegment->dstStation=metroStation;
    }
        
}

short deleteSegment(SDL_Renderer *mainRenderer, SDLBackground *background,MetroSegment ***arrMetroSegment,MetroSegment **currentMetroSegment, unsigned short *sizeArrMetroSegment){

    //Enlève le premier élément à supprimer de la liste chainée
    if((*currentMetroSegment)->precedentSegment!=NULL){
        (*currentMetroSegment)->precedentSegment->nextSegment=NULL;
    }

    //Supprime les éléments suivants 
    while((*currentMetroSegment)!=NULL){
        
        SDL_Rect absolutePathPointToDstPointRect= absoluteRectPositionInRect(&(*currentMetroSegment)->pathPointToDstPointRect,&(*currentMetroSegment)->rect);
        SDL_Rect absoluteSrcPointToPathPointRect= absoluteRectPositionInRect(&(*currentMetroSegment)->srcPointToPathPointRect,&(*currentMetroSegment)->rect);

        //Copie la portion d'image de fond n'étant plus recouverte par le segment supprimé
        if(SDL_RenderCopy(mainRenderer,background->texture,&absolutePathPointToDstPointRect,&absolutePathPointToDstPointRect)!=0||SDL_RenderCopy(mainRenderer,background->texture,&absoluteSrcPointToPathPointRect,&absoluteSrcPointToPathPointRect)!=0){
            fprintf(stderr,"Echec lors de la copie de la texture dans le rendu dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
            return 0;
        }

        SDL_RenderPresent(mainRenderer);

        //Passe à l'élement suivant et désalloue l'élément courant
        if((*currentMetroSegment)->nextSegment!=NULL){
            (*currentMetroSegment)=(*currentMetroSegment)->nextSegment;
            freeMetroSegment((*currentMetroSegment)->precedentSegment);
            free((*currentMetroSegment)->precedentSegment);
            (*currentMetroSegment)->precedentSegment=NULL;
        }
        else{
            freeMetroSegment(*currentMetroSegment);
            free(*currentMetroSegment);
            *currentMetroSegment=NULL;
        }
        (*sizeArrMetroSegment)--;
    }
    if((*sizeArrMetroSegment)>0){
        if(((*arrMetroSegment)=realloc((*arrMetroSegment),sizeof(MetroSegment*)*(*sizeArrMetroSegment)))==NULL){
            createErrorReport("Echec d'allocation memoire.",__FILE__,__LINE__,__DATE__,__TIME__);
            return 0;
        }
    }
    return 1;
}

short controlEngineOnLine(Engine ***arrEngine, int sizeArrEngine,MetroSegment **currentMetroSegment){

    for(int engineCounter=0; engineCounter<sizeArrEngine; engineCounter++){

        if((*arrEngine)[engineCounter]!=NULL && (*arrEngine)[engineCounter]->currentMetroSegment!=NULL ){
            MetroSegment *engineSegment=(*arrEngine)[engineCounter]->currentMetroSegment;
            printf("OK SEGMENT");
            while(engineSegment!=NULL){
                if(engineSegment==(*currentMetroSegment)){
                    printf("SUR SEGMENT");

                    return 0;
                }
                engineSegment=engineSegment->precedentSegment;
            }
        }
    }
    return 1;
}

MetroSegment *addNewSegment(MetroSegment ***arrMetroSegment, MetroStation **srcStation , MetroStation **dstStation, unsigned short *sizeArrMetroSegment,short *addBool ){

    void *voidSegment;
    short orderSegment=0;

    //Si la ligne est vide créer directement un segment
    if(*sizeArrMetroSegment==0){

        if(((*arrMetroSegment)=realloc((*arrMetroSegment),(++*sizeArrMetroSegment)*sizeof(MetroSegment*)))==NULL){
            createErrorReport("Echec d'allocation memoire.",__FILE__,__LINE__,__DATE__,__TIME__);
            return NULL;
        }
        if(((*arrMetroSegment)[*sizeArrMetroSegment-1]=malloc(sizeof(MetroSegment)))==NULL){
            createErrorReport("Echec d'allocation memoire.",__FILE__,__LINE__,__DATE__,__TIME__);
            return NULL;
        }
        (*arrMetroSegment)[*sizeArrMetroSegment-1]->precedentSegment=NULL;
        (*arrMetroSegment)[*sizeArrMetroSegment-1]->nextSegment=NULL;
        reorderSrcAndDestStations(&(*arrMetroSegment)[*sizeArrMetroSegment-1], srcStation, dstStation, 0);
        *addBool=1;      
        return (*arrMetroSegment)[*sizeArrMetroSegment-1];
    }
    //Si la ligne n'est pas vide on définie l'emplacement de la station et vérifie les doublons de stations en mettant à jour les liens entre les segments
    else{
        
        orderSegment=getSegmentWithOrder(arrMetroSegment,srcStation , dstStation,*sizeArrMetroSegment);

        if(orderSegment!=0){
            if(((*arrMetroSegment)=realloc((*arrMetroSegment),(++(*sizeArrMetroSegment))*sizeof(MetroSegment*)))==NULL){
                createErrorReport("Echec d'allocation memoire.",__FILE__,__LINE__,__DATE__,__TIME__);
                return NULL;
            }
            //Si un segment est créé en début de ligne, le tableau de segment est trié en y ajoutant le nouveau segment en début de tableau
            if(orderSegment==1){

                if(((*arrMetroSegment)[*sizeArrMetroSegment-1]=malloc(sizeof(MetroSegment)))==NULL){
                    createErrorReport("Echec d'allocation memoire.",__FILE__,__LINE__,__DATE__,__TIME__);
                    return NULL;
                }
                reorderMetroSegmentsLastToFirst(arrMetroSegment,*sizeArrMetroSegment);
                (*arrMetroSegment)[0]->nextSegment=(*arrMetroSegment)[1];
                (*arrMetroSegment)[1]->precedentSegment=(*arrMetroSegment)[0];
                (*arrMetroSegment)[0]->precedentSegment=NULL;
                reorderSrcAndDestStations(&(*arrMetroSegment)[0], srcStation, dstStation, orderSegment); 
                *addBool=1;                   
                return (*arrMetroSegment)[0];
            }
            //Si un segment est créé en fin de ligne, on ajoute un élément en fin de tableau
            if(orderSegment==2){
                if(((*arrMetroSegment)[*sizeArrMetroSegment-1]=malloc(sizeof(MetroSegment)))==NULL){
                    createErrorReport("Echec d'allocation memoire.",__FILE__,__LINE__,__DATE__,__TIME__);
                    return NULL;
                }
                (*arrMetroSegment)[*sizeArrMetroSegment-1]->precedentSegment=(*arrMetroSegment)[*sizeArrMetroSegment-2];
                (*arrMetroSegment)[*sizeArrMetroSegment-2]->nextSegment=(*arrMetroSegment)[*sizeArrMetroSegment-1];
                (*arrMetroSegment)[*sizeArrMetroSegment-1]->nextSegment=NULL;
                reorderSrcAndDestStations(&(*arrMetroSegment)[*sizeArrMetroSegment-1], srcStation, dstStation, orderSegment); 
                *addBool=1;       
                return (*arrMetroSegment)[*sizeArrMetroSegment-1];
            } 
        }
        else{
            *addBool=0;
        }
    }
    return voidSegment;
}

short getSegmentWithOrder(MetroSegment ***arrMetroSegment,MetroStation **srcStation , MetroStation **dstStation, unsigned short sizeArrSegment){

    MetroSegment *segment;
    short srcStationCounter=0;
    short dstStationCounter=0;

    if((*arrMetroSegment)[0]!=NULL){
        segment=(*arrMetroSegment)[0];
    }

    //Vérifie que la nouvelle station n'est pas déja présente dans la ligne de métro
    while(segment!=NULL){
        if(segment->srcStation==*dstStation||segment->dstStation==*dstStation){
            dstStationCounter ++;
        }
        if(segment->srcStation==*srcStation||segment->dstStation==*srcStation){
            srcStationCounter++;
        }
        segment=segment->nextSegment;
    }
    if(srcStationCounter>0 && dstStationCounter>0){
        return 0;
    }

    //Si la station ciblée se trouve en bout de ligne retourne 2
    if((*arrMetroSegment)[sizeArrSegment-1]->dstStation==*srcStation||(*arrMetroSegment)[sizeArrSegment-1]->dstStation==*dstStation){
        return 2;
    }
    //Si la station ciblée se trouve en début de ligne retourne 1
    if((*arrMetroSegment)[0]->srcStation==*srcStation||(*arrMetroSegment)[0]->srcStation==*dstStation){
        return 1;
    }
    return 0;
}

//
// ─── FONCTIONS DE CREATION DE SEGMENTS ET LIGNES DE METRO ───────────────────────
//


short SDLCreateMetroLineMenu(SDLBackground *backgroundMenu){
    
    for(unsigned short counterMetroLine=0; counterMetroLine<backgroundMenu->sizeArrMetroLines; counterMetroLine++){


        short randValue=rand()%backgroundMenu->sizeArrMetroStations;

        if((backgroundMenu->arrMetroLines[counterMetroLine]=malloc(sizeof(MetroLine)))==NULL){
            createErrorReport("Echec d'allocation memoire.",__FILE__,__LINE__,__DATE__,__TIME__);
            return 0;
        }

        backgroundMenu->arrMetroLines[counterMetroLine]->color=backgroundMenu->arrMetroLinesColor[counterMetroLine];

        backgroundMenu->arrMetroLines[counterMetroLine]->sizeArrSegment =rand()%(backgroundMenu->sizeArrMetroStations/2)+2;

        if((backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment = calloc(backgroundMenu->arrMetroLines[counterMetroLine]->sizeArrSegment,sizeof(MetroSegment*)))==NULL){
            return 0;
            createErrorReport("Echec d'allocation memoire.",__FILE__,__LINE__,__DATE__,__TIME__);
        }

        backgroundMenu->arrMetroLines[counterMetroLine]->srcMetroStation=backgroundMenu->arrMetroStations[randValue];
    }
    return 1;

}

short SDLCreateMetroSegmentMenu(SDLBackground *backgroundMenu){

    for(unsigned short counterMetroLine=0;counterMetroLine<backgroundMenu->sizeArrMetroLines;counterMetroLine++){
        if(backgroundMenu->arrMetroLines[counterMetroLine]!=0){
            for(unsigned short counterMetroSegment=0; counterMetroSegment<backgroundMenu->arrMetroLines[counterMetroLine]->sizeArrSegment;counterMetroSegment++){
                if((backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]=malloc(sizeof(MetroSegment)))==NULL){
                    createErrorReport("Echec d'allocation memoire.",__FILE__,__LINE__,__DATE__,__TIME__);           
                    return 0;
                }
                backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->surface=NULL;
                backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->texture=NULL;

                if(counterMetroSegment==0){
                    backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->precedentSegment=NULL;
                }
                else{
                    backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->precedentSegment=backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment-1];
                }

                linkMetroSegmentMetroStation( 
                backgroundMenu->arrMetroLines[counterMetroLine]->srcMetroStation->arrOtherMetroStations[counterMetroSegment],
                backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment],0);

                linkMetroSegmentMetroStation( 
                backgroundMenu->arrMetroLines[counterMetroLine]->srcMetroStation->arrOtherMetroStations[counterMetroSegment+1],
                backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment],1);

                createGeometryMetroSegment(
                    backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment],
                    backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->precedentSegment, 
                    backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->srcStation, 
                    backgroundMenu->arrMetroLines[counterMetroLine]->arrMetroSegment[counterMetroSegment]->dstStation, 
                    counterMetroLine,  backgroundMenu->metroLineThickness);
            }
        }     
    }
    return 1;    
}




