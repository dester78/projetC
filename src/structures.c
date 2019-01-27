#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <structures.h>
#include <formatString.h>
#include <fileManager.h>


FileIndex * initFileIndex(){

    FileIndex *fileIndex;

    fileIndex=malloc(sizeof(FileIndex));

    // fileIndex->err=returnFileElement("errorLog.txt","a+");
    fileIndex->config=returnFileElement("popTube.cfg","r+");
    fileIndex->config->filePointer=NULL;
    fileIndex->metroLineColor=returnFileElement("txt/metroLineColors.txt","r");
    fileIndex->metroLineColor->filePointer=NULL;


    return fileIndex;

}

File *returnFileElement(char *fullName, char* openMode  ){

    File *fileElement;

    fileElement=malloc(sizeof(File));

    if((fileElement->fullName=malloc(sizeof(char)*(strlen( fullName )+1 ) ) ) != NULL){

        if(strcpy(fileElement->fullName,fullName)==NULL){
            createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
        }
    }

    else{
        createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
    }

    if(strlen(openMode)<=3){

        if(strcpy(fileElement->openMode,openMode)==NULL){
            createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
        }
    }

    else{
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

void freeFileIndex(FileIndex *fileIndex){

    // freeFileElement(fileIndex->err);
    freeFileElement(fileIndex->config);
    free(fileIndex->config);

    freeFileElement(fileIndex->metroLineColor);
    free(fileIndex->metroLineColor);

}


void freeFileElement(File *fileElement){

    free(fileElement->fullName);
    if(fileElement->filePointer!=NULL){
        fclose(fileElement->filePointer);
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