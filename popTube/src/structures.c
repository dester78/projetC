#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <structures.h>
#include <formatString.h>
#include <fileManager.h>

Files returnFileElement(char *fullName, char* openMode ){

    Files fileElement;

    if((fileElement.fullName=malloc(sizeof(char)*(strlen( fullName )+1 ) ) ) != NULL){

        if(strcpy(fileElement.fullName,fullName)==NULL){
            createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
        }

    }
    else{
        createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
    }

    if(strlen(openMode)<=3){

        if(strcpy(fileElement.openMode,openMode)==NULL){
            createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
        }
    }

    else{
        createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
    }
    
    if((fileElement.filePointer=malloc(sizeof(FILE)))==NULL){

        createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
    }

    return fileElement;
}


int initDbConfig(DbConfig *dbConfigElement, char **arrayParameters,int lastRow ){

    int counterParameters=0;
    
    while( counterParameters< lastRow){
    
        if( strncmp(arrayParameters[counterParameters], "host=" , strlen("host=")) == 0){

            if((dbConfigElement->host = malloc( sizeof(char) * strlen(arrayParameters[counterParameters]) - strlen("host="))) != NULL){
                strcpy(dbConfigElement->host , (arrayParameters[counterParameters]+ strlen("host=")));
            }

            else{
                createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }

        else if( strncmp(arrayParameters[counterParameters],"user=",strlen("user=")) == 0){

            if( (dbConfigElement->user = malloc(sizeof(char)*strlen(arrayParameters[counterParameters])- strlen("user=")))!= NULL){
                strcpy(dbConfigElement->user,(arrayParameters[counterParameters]+ strlen("user=")));

                if(strcmp(dbConfigElement->user,"root")==0){

                    if((dbConfigElement->passwd = malloc(sizeof(char)*strlen("root")))!= NULL){
                            strcpy(dbConfigElement->passwd,"root");
                    }
                    else{
                        createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
                        return 0;
                    }
                }
            }
            else{
                createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }

        else if(strncmp(arrayParameters[counterParameters],"db=",strlen("db=")) == 0){
            
            if((dbConfigElement->db = malloc(sizeof(char)*strlen(arrayParameters[counterParameters])- strlen("db=")))!= NULL){
                strcpy(dbConfigElement->db,(arrayParameters[counterParameters]+ strlen("db=")));
            }
            else{
                createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }

        else if(strncmp(arrayParameters[counterParameters],"playerLogin=",strlen("playerLogin=")) == 0){
            
            if((dbConfigElement->playerLogin = malloc(sizeof(char)*strlen(arrayParameters[counterParameters])- strlen("playerLogin=")))!= NULL){
                strcpy(dbConfigElement->playerLogin,(arrayParameters[counterParameters]+ strlen("playerLogin=")));
            }
            else{
                createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }

        else if(strncmp(arrayParameters[counterParameters],"playerPasswd=",strlen("playerPasswd=")) == 0){
            
            if((dbConfigElement->playerPasswd = malloc(sizeof(char)*strlen(arrayParameters[counterParameters])- strlen("playerPasswd=")))!= NULL){
                strcpy(dbConfigElement->playerPasswd,(arrayParameters[counterParameters]+ strlen("playerPasswd=")));
            }
            else{
                createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }
        counterParameters++;
    }

    return 1;
}

int initSDLConfig(SDLConfig *SDLConfigElement,char **arrayParameters, int lastRow ){

    if((SDLConfigElement->window=(malloc(sizeof(SDLWindowConfig))))!=NULL){

        initSDLWindowConfig(SDLConfigElement->window ,arrayParameters, lastRow);
    }

    else{
        createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;
    }
    

    if((SDLConfigElement->init=(malloc(sizeof(SDLInitConfig))))!=NULL){

        initSDLInitConfig(SDLConfigElement->init ,arrayParameters, lastRow);

    }

    else{
        createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;
    }

    if((SDLConfigElement->renderer=(malloc(sizeof(SDLRendererConfig))))!=NULL){

        initSDLRendererConfig(SDLConfigElement->renderer ,arrayParameters, lastRow);

    }

    else{
        createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;
    }

    if((SDLConfigElement->ttf=(malloc(sizeof(TTFConfig))))!=NULL){

        initTTFConfig(SDLConfigElement->ttf ,arrayParameters, lastRow);

    }

    else{
        createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;
    }

    return 1;
    
    
}


void freeSDLConfigElement(SDLConfig *SDLConfigElement){

    free(SDLConfigElement->window);
    free(SDLConfigElement->init);
    free(SDLConfigElement->renderer);
    free(SDLConfigElement->ttf->fontMenu);
    free(SDLConfigElement->ttf);
}



void initSDLWindowConfig(SDLWindowConfig *windowConfigElement, char **arrayParameters, int lastRow ){

    int counterParameters=0;
    windowConfigElement->windowFlag=0x00000000;
    windowConfigElement->windowHeight=0;
    windowConfigElement->windowWidth=0;

    while( counterParameters<lastRow ){

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
        counterParameters++;
    }

}

void initSDLRendererConfig(SDLRendererConfig *rendererConfigElement, char **arrayParameters, int lastRow ){

    int counterParameters=0;
    rendererConfigElement->rendererFlag=0x00000000;
    
    while( counterParameters<lastRow ){

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

void initTTFConfig(TTFConfig *ttfConfigElement, char **arrayParameters,int lastRow ){

    int counterParameters=0;

    ttfConfigElement->fontDirectory="fonts/";

    while( counterParameters< lastRow){

        if( strncmp(arrayParameters[counterParameters], "fontDirectory=" , strlen("fontDirectory=")) == 0){

            free(ttfConfigElement->fontDirectory);

            if((ttfConfigElement->fontDirectory = malloc( sizeof(char) * (strlen(arrayParameters[counterParameters]) - strlen("fontDirectory="))+1)) != NULL){
                
                strcpy(ttfConfigElement->fontDirectory , (arrayParameters[counterParameters]+ strlen("fontDirectory=")));
                formatFullPath(&ttfConfigElement->fontDirectory);
            }

            else{
                createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
            }
        }
        counterParameters++;
    }

    counterParameters=0;

    while( counterParameters< lastRow){
    
        if( strncmp(arrayParameters[counterParameters], "fontMenu=" , strlen("fontMenu=")) == 0){

            if((ttfConfigElement->fontMenu = malloc( sizeof(char) * strlen(arrayParameters[counterParameters]) - strlen("fontMenu=")+strlen(ttfConfigElement->fontDirectory))) != NULL){
                strcpy(ttfConfigElement->fontMenu , ttfConfigElement->fontDirectory);
                strcat(ttfConfigElement->fontMenu , (arrayParameters[counterParameters]+ strlen("fontMenu=")));
            }

            else{
                createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
            }
        }
        counterParameters++;
    }
}

void freeDbConfigElement(DbConfig *dbConfigElement){


    free(dbConfigElement->host);
    free(dbConfigElement->user);
    free(dbConfigElement->passwd);
    free(dbConfigElement->db);
    free(dbConfigElement->playerLogin);
    free(dbConfigElement->playerPasswd);
    
}

void freeFileElement(Files fileElement){

    fclose(fileElement.filePointer);
}

