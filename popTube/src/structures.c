#include <structures.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void initDbConfig(DbConfig *dbConfigElement, char **arrayParameters,int lastRow){

    int counterParameters=0;
    printf("%d",lastRow);
    
    while( counterParameters< lastRow){
    
        if( strncmp(arrayParameters[counterParameters], "host=" , strlen("host=")) == 0){

            if((dbConfigElement->host = malloc( sizeof(char) * strlen(arrayParameters[counterParameters]) - strlen("host="))) != NULL){
                strcpy(dbConfigElement->host , (arrayParameters[counterParameters]+ strlen("host=")));
            }

            else{
                printf("Erreur lors de l'allocation de host dans la structure dbConfigElement dans la fonction %s",__func__);
            }
        }

        else if( strncmp(arrayParameters[counterParameters],"user=",strlen("user=")) == 0){

            if( (dbConfigElement->user = malloc(sizeof(char)*strlen(arrayParameters[counterParameters])- strlen("user=")))!= NULL){
                strcpy(dbConfigElement->user,(arrayParameters[counterParameters]+ strlen("user=")));
            }
            else{
                printf("Erreur lors de l'allocation de host dans la structure dbConfigElement dans la fonction %s",__func__);
            }
        }

        else if(strncmp(arrayParameters[counterParameters],"passwd=",strlen("passwd=")) == 0){

            if((dbConfigElement->passwd = malloc(sizeof(char)*strlen(arrayParameters[counterParameters])- strlen("passwd=")))!= NULL){
                strcpy(dbConfigElement->passwd,(arrayParameters[counterParameters]+ strlen("passwd=")));
            }
            else{
                printf("Erreur lors de l'allocation de host dans la structure dbConfigElement dans la fonction %s",__func__);
            }
        }

        else if(strncmp(arrayParameters[counterParameters],"db=",strlen("db=")) == 0){
            
            if((dbConfigElement->db = malloc(sizeof(char)*strlen(arrayParameters[counterParameters])- strlen("db=")))!= NULL){
                strcpy(dbConfigElement->db,(arrayParameters[counterParameters]+ strlen("db=")));
            }
            else{
                printf("Erreur lors de l'allocation de host dans la structure dbConfigElement dans la fonction %s",__func__);
            }
        }
        counterParameters++;
    }
}

void initSDLConfig(SDLConfig *SDLConfigElement,char **arrayParameters, int lastRow){

    SDLConfigElement->window=(malloc(sizeof(SDLWindowConfig*)));
    SDLConfigElement->init=(malloc(sizeof(SDLInitConfig*)));

    initSDLWindowConfig(SDLConfigElement->window ,arrayParameters, lastRow);
    initSDLInitConfig(SDLConfigElement->init ,arrayParameters, lastRow);

}


void freeSDLConfigElement(SDLConfig *SDLConfigElement){


    free(SDLConfigElement->window->windowFlag);
    free(SDLConfigElement->init->initFlag);
    free(SDLConfigElement->window);
    free(SDLConfigElement->init);
}



void initSDLWindowConfig(SDLWindowConfig *windowConfigElement, char **arrayParameters, int lastRow){

    int counterParameters=0;
    windowConfigElement->windowFlag=0x00000000;
    
    while( counterParameters<lastRow ){


        if( strncmp(arrayParameters[counterParameters], "SDL_WindowFlags=" , strlen("SDL_WindowFlags=")) == 0){

            if(strstr(arrayParameters[counterParameters],"SDL_WINDOW_FULLSCREEN")!=NULL){
                windowConfigElement->windowFlag=windowConfigElement->windowFlag|SDL_WINDOW_FULLSCREEN;
            }
            else if(strstr(arrayParameters[counterParameters],"SDL_WINDOW_SHOWN")!=NULL){
                windowConfigElement->windowFlag=windowConfigElement->windowFlag|SDL_WINDOW_SHOWN;
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

void freeDbConfigElement(DbConfig *dbConfigElement){


    free(dbConfigElement->host);
    free(dbConfigElement->user);
    free(dbConfigElement->passwd);
    free(dbConfigElement->db);
    
}
