#include <stdlib.h>
#include <stdio.h>

#include <SDLColor.h>

#include <SDL.h>



/*
 * ─── FONCTION DE MANIPULATION DE PIXELS ─────────────────────────────────────────
 */
Uint32 getpixel(SDL_Surface *surface, int x, int y){

    int bpp = surface->format->BytesPerPixel;

    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;   
    }
}

short searchColorInSurface(SDL_Color *searchedColor, SDL_Rect *targetRect, SDL_Surface *surface, int accuracy){

    Uint32 pixel;
    SDL_Color pixelColor;

    if(SDL_LockSurface(surface)!=0){
        fprintf(stderr,"Echec lors du verrouillage d'une surface dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return -1;
    }
    for(int yCounter = targetRect->y ; yCounter<targetRect->y + targetRect->h - accuracy; yCounter++ ){
        for(int xCounter = targetRect->x ; xCounter<targetRect->x + targetRect->w - accuracy; xCounter++){
            
            pixel=getpixel(surface,xCounter,yCounter);
            SDL_GetRGBA(pixel,surface->format,&pixelColor.r, &pixelColor.g,&pixelColor.b,&pixelColor.a);

            if(SDLCompareColor(searchedColor,&pixelColor)){
                SDL_UnlockSurface(surface);
                return 1;
            }     
        }
    }    	
    SDL_UnlockSurface(surface);
    return 0;
}

/*
 * ─── FONCTION DE MANIPULATION DE COULEURS ───────────────────────────────────────
 */




SDL_Color SDLChangeRGBColor(int r, int g, int b , int a ){

    SDL_Color RGBColor;

    RGBColor.r=setOverflawColorComponent(r);
    RGBColor.g=setOverflawColorComponent(g);
    RGBColor.b=setOverflawColorComponent(b);
    RGBColor.a=setOverflawColorComponent(a);

    return RGBColor;
}

short SDLCompareColor(SDL_Color *firstColor, SDL_Color *secondColor){

    if(firstColor->r==secondColor->r&&firstColor->g==secondColor->g&&firstColor->b==secondColor->b&&firstColor->a==secondColor->a){
        return 1;
    }
    return 0;
}

void returnRandomColor(SDL_Color **arrColors, unsigned short sizeArrColor){

    SDL_Color tmpColor;
    
    //On parcours le tableau de couleurs donné en paramètre pour y affecter des SDL_Color uniques
    for(unsigned short counterColor=0; counterColor < sizeArrColor; counterColor++ ){

        short unikColor=1;
        switch((rand()%sizeArrColor)+1){

            case 1 :
                tmpColor=SDLChangeRGBColor(35,63,68,255);
            break; 

            case 2 : 
                tmpColor=SDLChangeRGBColor(165,93,8,255);
            break; 

            case 3 : 
                tmpColor=SDLChangeRGBColor(143,17,91,255);
            break; 

            case 4 : 
                tmpColor=SDLChangeRGBColor(225,155,223,255);
            break;

            case 5 : 
                tmpColor=SDLChangeRGBColor(110,202,151,255);
            break;

            case 6 : 
                tmpColor=SDLChangeRGBColor(0,60,166,255);
            break;

            case 7 : 
                tmpColor=SDLChangeRGBColor(168,16,50,255);
            break;
        }

        if(SDLCompareColor(&(*arrColors)[counterColor],&tmpColor)==0){

            //Parcours les couleurs précédentes pour vérifier que la couleur sélectionnée est unique dans le tableau 
            for(short counterColorBis=counterColor-1; counterColorBis>=0 ; counterColorBis-- ){
                
                if(SDLCompareColor(&(*arrColors)[counterColorBis],&tmpColor)){
                    unikColor=0;
                    break;
                }
            }
            if(unikColor){
                (*arrColors)[counterColor]=tmpColor;
            }
            //Si elle n'est pas unique on recommence le choix de la couleur et les véirifcations précédentes
            else{
                counterColor--;
            }
        } 
    }
}

int setOverflawColorComponent(int precedentComponent){

    precedentComponent=precedentComponent<0?0:precedentComponent;
    precedentComponent=precedentComponent>255?255:precedentComponent;
    return precedentComponent;
}

/*
 * ─── FONCTIONS NON UTILISEES ─────────────────────────────────────────────────────
 */

short replaceColorInSurface(SDL_Color *searchedColor,SDL_Color *replaceColor, SDL_Rect *targetRect, SDL_Surface *surface ){

    Uint32 *pixels;
    Uint32 pixel;
    SDL_Color pixelColor;
    SDL_Rect tmpTargetRect;

    if(targetRect==NULL){
        tmpTargetRect.x=0;
        tmpTargetRect.y=0;
        tmpTargetRect.h=surface->h;
        tmpTargetRect.w=surface->w;
    }
    else{
        tmpTargetRect=*targetRect;
    }
    if(SDL_LockSurface(surface)!=0){
        fprintf(stderr,"Echec lors du verrouillage d'une surface dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,SDL_GetError());
        return -1;
    }
    pixels=(Uint32*)surface->pixels;
    for(int yCounter = tmpTargetRect.y ; yCounter<tmpTargetRect.y + tmpTargetRect.h;  yCounter++ ){
        for(int xCounter = tmpTargetRect.x ; xCounter<tmpTargetRect.x + tmpTargetRect.w;  xCounter++){
            
            pixel=getpixel(surface,xCounter,yCounter);
            SDL_GetRGBA(pixel,surface->format,&pixelColor.r, &pixelColor.g,&pixelColor.b,&pixelColor.a);

            if(SDLCompareColor(searchedColor,&pixelColor)){
                pixels[yCounter*surface->pitch + xCounter* surface->w]=SDL_MapRGBA(surface->format,replaceColor->r,replaceColor->g,replaceColor->b,replaceColor->a);
            }     
        }
    }    
    SDL_UnlockSurface(surface);

    return 1;	
}