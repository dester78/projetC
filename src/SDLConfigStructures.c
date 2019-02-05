#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <SDLConfigStructures.h>
#include <fileManager.h>
#include <formatString.h>

#include <SDL.h>

/*
 * ─── FONCTIONS D'INITIALISATION DE STRUCTURES ────────────────────────────────────
 */


short initSDLConfig(SDLConfig *SDLConfigElement,char **arrayParameters, int lastRow ){

    if((SDLConfigElement->window=(malloc(sizeof(SDLWindowConfig))))==NULL){
        createErrorReport("Echec d'allocation memoire.",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;    
    }
    if(initSDLWindowConfig(SDLConfigElement->window ,arrayParameters, lastRow)==0){
        createErrorReport("Echec lors de l'initialisation de la configuration de la fenetre.",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;    
    }

    if((SDLConfigElement->init=(malloc(sizeof(SDLInitConfig))))==NULL){
        createErrorReport("Echec d'allocation memoire.",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;  
    }

    initSDLInitConfig(SDLConfigElement->init ,arrayParameters, lastRow);



    if((SDLConfigElement->renderer=(malloc(sizeof(SDLRendererConfig))))==NULL){
        createErrorReport("Echec d'allocation memoire.",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;    

    }
    
    initSDLRendererConfig(SDLConfigElement->renderer ,arrayParameters, lastRow);


    if((SDLConfigElement->ttf=(malloc(sizeof(TTFConfig))))==NULL){
        createErrorReport("Echec d'allocation memoire.",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;   
        

    }
    if(initTTFConfig(SDLConfigElement->ttf ,arrayParameters, lastRow)==0){
        createErrorReport("Echec lors de l'initialisation de la configuration de la SDL TFF.",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0; 
    }


    if((SDLConfigElement->img=(malloc(sizeof(IMGConfig))))==NULL){
        createErrorReport("Echec d'allocation memoire.",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;  
    }

    return 1;

}

short initSDLWindowConfig(SDLWindowConfig *windowConfigElement, char **arrayParameters, int lastRow ){

    int counterParameters=0;
    windowConfigElement->windowFlag=0x00000000;
    windowConfigElement->windowHeight=0;
    windowConfigElement->windowWidth=0;
    

    while( counterParameters<lastRow ){
        errno=0;
        if( strncmp(arrayParameters[counterParameters], "SDL_WindowFlags=" , strlen("SDL_WindowFlags=")) == 0){

            if(strstr(arrayParameters[counterParameters],"SDL_WINDOW_FULLSCREEN")!=NULL){
                windowConfigElement->windowFlag=windowConfigElement->windowFlag|SDL_WINDOW_FULLSCREEN;
            }
            else if(strstr(arrayParameters[counterParameters],"SDL_WINDOW_SHOWN")!=NULL){
                windowConfigElement->windowFlag=windowConfigElement->windowFlag|SDL_WINDOW_SHOWN;
            }
        }
       
        else if( strncmp(arrayParameters[counterParameters], "windowHeight=" , strlen("windowHeight=")) == 0){
            
            windowConfigElement->windowHeight=atoi( arrayParameters[counterParameters]+ strlen("windowHeight="));
        }

        else if( strncmp(arrayParameters[counterParameters], "windowWidth=" , strlen("windowWidth=")) == 0){
            
            windowConfigElement->windowWidth=atoi( arrayParameters[counterParameters]+ strlen("windowWidth="));
        }
        if(errno==ERANGE){
            createErrorReport("La taille de la fenetre du fichier de configuration depasse les valeurs admise par ce programme",__FILE__,__LINE__,__DATE__,__TIME__);
            return 0;
        }
        counterParameters++;
    }
    return 1;

}

void initSDLInitConfig(SDLInitConfig *initConfigElement, char **arrayParameters, int lastRow){

    int counterParameters=0;
    initConfigElement->initFlag=0x00000000;
    
    while( counterParameters<lastRow ){

        if( strncmp(arrayParameters[counterParameters], "SDL_InitFlags=" , strlen("SDL_InitFlags=")) == 0){

            if(strstr(arrayParameters[counterParameters],"SDL_INIT_TIMER")!=NULL){
                initConfigElement->initFlag=initConfigElement->initFlag|SDL_INIT_TIMER;
            }
            else if(strstr(arrayParameters[counterParameters],"SDL_INIT_AUDIO")!=NULL){
                initConfigElement->initFlag=initConfigElement->initFlag|SDL_INIT_AUDIO;
            }
            else if(strstr(arrayParameters[counterParameters],"SDL_INIT_VIDEO")!=NULL){
                initConfigElement->initFlag=initConfigElement->initFlag|SDL_INIT_VIDEO;
            }
            else if(strstr(arrayParameters[counterParameters],"SDL_INIT_JOYSTICK")!=NULL){
                initConfigElement->initFlag=initConfigElement->initFlag|SDL_INIT_JOYSTICK;
            }
            else if(strstr(arrayParameters[counterParameters],"SDL_INIT_HAPTIC")!=NULL){
                initConfigElement->initFlag=initConfigElement->initFlag|SDL_INIT_HAPTIC;
            }
            else if(strstr(arrayParameters[counterParameters],"SDL_INIT_GAMECONTROLLER")!=NULL){
                initConfigElement->initFlag=initConfigElement->initFlag|SDL_INIT_GAMECONTROLLER;
            }
            else if(strstr(arrayParameters[counterParameters],"SDL_INIT_SENSOR")!=NULL){
                initConfigElement->initFlag=initConfigElement->initFlag|SDL_INIT_SENSOR;
            }
            else if(strstr(arrayParameters[counterParameters],"SDL_INIT_NOPARACHUTE")!=NULL){
                initConfigElement->initFlag=initConfigElement->initFlag|SDL_INIT_NOPARACHUTE;
            }
            else if(strstr(arrayParameters[counterParameters],"SDL_INIT_EVERYTHING")!=NULL){
                initConfigElement->initFlag=initConfigElement->initFlag|SDL_INIT_EVERYTHING;
            }
        }
        counterParameters++;
    }
}

void initSDLRendererConfig(SDLRendererConfig *rendererConfigElement, char **arrayParameters, int lastRow ){

    int counterParameters=0;
    rendererConfigElement->rendererFlag=0x00000000;
    
    while( counterParameters<lastRow ){

        errno=0;
        if( strncmp(arrayParameters[counterParameters], "SDL_RendererFlags=" , strlen("SDL_RendererFlags=")) == 0){

            if(strstr(arrayParameters[counterParameters],"SDL_RENDERER_ACCELERATED")!=NULL){
                rendererConfigElement->rendererFlag=rendererConfigElement->rendererFlag|SDL_RENDERER_ACCELERATED;
            }
            else if(strstr(arrayParameters[counterParameters],"SDL_RENDERER_PRESENTVSYNC")!=NULL){
                rendererConfigElement->rendererFlag=rendererConfigElement->rendererFlag|SDL_RENDERER_PRESENTVSYNC;
            }
            else if(strstr(arrayParameters[counterParameters],"SDL_RENDERER_TARGETTEXTURE")!=NULL){
                rendererConfigElement->rendererFlag=rendererConfigElement->rendererFlag|SDL_RENDERER_TARGETTEXTURE;
            }
            else if(strstr(arrayParameters[counterParameters],"SDL_RENDERER_SOFTWARE")!=NULL){
                rendererConfigElement->rendererFlag=rendererConfigElement->rendererFlag|SDL_RENDERER_SOFTWARE;
            }
        }
        counterParameters++;
    }
}

short initTTFConfig(TTFConfig *ttfConfigElement, char **arrayParameters,int lastRow ){

    int counterParameters=0;

    if((ttfConfigElement->fontDirectory=malloc(sizeof(char)*strlen("fonts/")+1))==NULL){
        createErrorReport("Echec d'allocation memoire.",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;   
    }

    if(strcpy(ttfConfigElement->fontDirectory,"fonts/")==NULL){
        createErrorReport("Echec lors de la copie d'une chaine de caractere",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;
    }

    while( counterParameters< lastRow){

        if( strncmp(arrayParameters[counterParameters], "fontDirectory=" , strlen("fontDirectory=")) == 0){

            free(ttfConfigElement->fontDirectory);

            if((ttfConfigElement->fontDirectory = calloc( (strlen(arrayParameters[counterParameters]) - strlen("fontDirectory="))+1,sizeof(char))) == NULL){
                createErrorReport("Echec d'allocation memoire.",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;   
            }
            if((strcpy(ttfConfigElement->fontDirectory , (arrayParameters[counterParameters]+ strlen("fontDirectory="))))==NULL){
                createErrorReport("Echec lors de la copie d'une chaine de caractere",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
            if(formatFullPath(&ttfConfigElement->fontDirectory)==0){
                createErrorReport("Echec lors du formatage d'un chemin absolue.",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }
        counterParameters++;
    }

    counterParameters=0;

    while( counterParameters< lastRow){
    
        if( strncmp(arrayParameters[counterParameters], "fontMenu=" , strlen("fontMenu=")) == 0){

            if((ttfConfigElement->fontMenu = calloc(strlen(arrayParameters[counterParameters]) - strlen("fontMenu=")+strlen(ttfConfigElement->fontDirectory),sizeof(char))) == NULL){
                createErrorReport("Echec d'allocation memoire.",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;   
            }        
            if(strcpy(ttfConfigElement->fontMenu , ttfConfigElement->fontDirectory)==NULL){
                createErrorReport("Echec lors de la copie d'une chaine de caractere",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
            if(strcat(ttfConfigElement->fontMenu , (arrayParameters[counterParameters]+ strlen("fontMenu=")))==NULL){
                createErrorReport("Echec lors de la concatenation de deux chaines de caracteres",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }
        counterParameters++;
    }
    return 1;
}

short initIMGConfig(IMGConfig *IMGConfigElement, char **arrayParameters,int lastRow , int windowWidth, int windowHeight){

    int counterParameters=0;
    int stringDimensions[2]={0};

    if((IMGConfigElement->IMGDirectory=malloc(sizeof(char)*strlen("img/")+1))==NULL){
        createErrorReport("Echec d'allocation memoire.",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;   
    }
    if(strcpy(IMGConfigElement->IMGDirectory,"img/")==NULL){
        createErrorReport("Echec lors de la copie d'une chaine de caractere",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;
    }

    while( counterParameters< lastRow){

        if( strncmp(arrayParameters[counterParameters], "parisMap=" , strlen("parisMap=")) == 0){

            if((IMGConfigElement->parisMap = calloc(strlen(IMGConfigElement->IMGDirectory)+strlen(arrayParameters[counterParameters]) - strlen("parisMap=")+1,sizeof(char))) == NULL){
                createErrorReport("Echec d'allocation memoire.",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
            if(extractWindowDimensionsFromString(arrayParameters[counterParameters]+ strlen("parisMap="),stringDimensions)==0){
                createErrorReport("Erreur lors de l'extraction des dimensions de d'une image dans le fichier de configuration",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
            //Trouve l'image ayant les dimensions les plus proches de celles de la fenêtre
            if(windowWidth>=stringDimensions[0] || windowHeight>=stringDimensions[1]){
                if(IMGConfigElement->parisMap!=NULL){
                    free(IMGConfigElement->parisMap);
                    if((IMGConfigElement->parisMap = calloc(strlen(IMGConfigElement->IMGDirectory)+strlen(arrayParameters[counterParameters]) - strlen("parisMap=")+1,sizeof(char))) == NULL){
                        createErrorReport("Echec d'allocation memoire.",__FILE__,__LINE__,__DATE__,__TIME__);
                        return 0;
                    }
                }
                
                if(strcpy(IMGConfigElement->parisMap,IMGConfigElement->IMGDirectory)==NULL){
                    createErrorReport("Echec lors de la copie d'une chaine de caractere",__FILE__,__LINE__,__DATE__,__TIME__);
                    return 0;
                }

                if(strcat(IMGConfigElement->parisMap , (arrayParameters[counterParameters]+ strlen("parisMap=")))==NULL){
                    createErrorReport("Echec lors de la concatenation de deux chaines de caracteres",__FILE__,__LINE__,__DATE__,__TIME__);
                    return 0;
                }  
                if(windowWidth==stringDimensions[0] && windowHeight==stringDimensions[1]){
                    break;
                }                
            }
        }
        counterParameters++;
    }
    return 1;
}

/*
 * ─── FONCTIONS DE LIBERATION D'ALLOCATION ────────────────────────────────────
 */


void freeSDLConfigElement(SDLConfig *SDLConfigElement){

    free(SDLConfigElement->window);
    free(SDLConfigElement->init);
    free(SDLConfigElement->renderer);
    free(SDLConfigElement->ttf->fontDirectory);
    free(SDLConfigElement->ttf->fontMenu);
    free(SDLConfigElement->ttf);

    free(SDLConfigElement->img->IMGDirectory);    
    free(SDLConfigElement->img->parisMap);
    free(SDLConfigElement->img);
}

