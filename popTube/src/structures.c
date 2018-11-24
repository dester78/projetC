#include <structures.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void initDbConfig(DbConfig *dbConfigElement, char ***arrayParameters){

    int counterParameters=0;
    
    while( *(*arrayParameters + counterParameters)!=NULL){
    
        if( strncmp(*(*arrayParameters + counterParameters) , "host=" , strlen("host=")) == 0){

            dbConfigElement->host = malloc( sizeof(char*) * strlen(*(*arrayParameters + counterParameters)) - strlen("host="));

            if(dbConfigElement->host != NULL){
                strcpy(dbConfigElement->host , (*(*arrayParameters + counterParameters) + strlen("host=")));
            }
        }

        else if( strncmp(*(*arrayParameters+counterParameters),"user=",strlen("user=")) == 0){

            dbConfigElement->user = malloc(sizeof(char*)*strlen(*(*arrayParameters+counterParameters))- strlen("user="));
            
            if(dbConfigElement->user != NULL){
                strcpy(dbConfigElement->user,(*(*arrayParameters+counterParameters)+ strlen("user=")));
            }
        }

        else if(strncmp(*(*arrayParameters+counterParameters),"passwd=",strlen("passwd=")) == 0){

            dbConfigElement->passwd = malloc(sizeof(char*)*strlen(*(*arrayParameters+counterParameters))- strlen("passwd="));
            
            if(dbConfigElement->passwd != NULL){
                strcpy(dbConfigElement->passwd,(*(*arrayParameters+counterParameters)+ strlen("passwd=")));
            }
        }

        else if(strncmp(*(*arrayParameters+counterParameters),"db=",strlen("db=")) == 0){

            dbConfigElement->db = malloc(sizeof(char*)*strlen(*(*arrayParameters+counterParameters))- strlen("db="));
            
            if(dbConfigElement->db != NULL){
                strcpy(dbConfigElement->db,(*(*arrayParameters+counterParameters)+ strlen("db=")));
            }
        }
        counterParameters++;
    }
}

void initSDLVideoConfig(SDLVideoConfig *videoConfigElement, char ***arrayParameters){

    int counterParameters=0;
    videoConfigElement->windowFlag=0x00000000;
    
    while( *(*arrayParameters + counterParameters)!=NULL ){

        if( strncmp(*(*arrayParameters + counterParameters) , "SDL_WindowFlags=" , strlen("SDL_WindowFlags=")) == 0){

            if(strstr(*(*arrayParameters + counterParameters),"SDL_WINDOW_FULLSCREEN")!=NULL){
                videoConfigElement->windowFlag=videoConfigElement->windowFlag|SDL_WINDOW_FULLSCREEN;
            }
            else if(strstr(*(*arrayParameters + counterParameters),"SDL_WINDOW_SHOWN")!=NULL){
                videoConfigElement->windowFlag=videoConfigElement->windowFlag|SDL_WINDOW_SHOWN;
            }
        }

        counterParameters++;
    }
}



