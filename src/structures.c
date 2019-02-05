#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <structures.h>
#include <formatString.h>
#include <fileManager.h>

/*
 * ─── FONCTIONS D'INITIALISATION DE STRUCTURES ────────────────────────────────────
 */

short initDbConfig(DbConfig *dbConfigElement, char **arrayParameters,int lastRow ){

    int counterParameters=0;
    
    while( counterParameters< lastRow){
    
        if( strncmp(arrayParameters[counterParameters], "host=" , strlen("host=")) == 0){
            if((dbConfigElement->host = malloc( sizeof(char) * strlen(arrayParameters[counterParameters]) - strlen("host="))) == NULL){
                createErrorReport("Echec lors d'une allocation memoire)",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }

            if(strcpy(dbConfigElement->host , (arrayParameters[counterParameters]+ strlen("host=")))==NULL){
                createErrorReport("Echec lors de la copie d'une chaine de caractere",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }

        else if( strncmp(arrayParameters[counterParameters],"user=",strlen("user=")) == 0){
            if( (dbConfigElement->user = malloc(sizeof(char)*strlen(arrayParameters[counterParameters])- strlen("user=")))== NULL){
                createErrorReport("Echec lors d'une allocation memoire)",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
            if(strcpy(dbConfigElement->user,(arrayParameters[counterParameters]+ strlen("user=")))==NULL){
                createErrorReport("Echec lors de la copie d'une chaine de caractere",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
            if(strcmp(dbConfigElement->user,"root")==0){
                if((dbConfigElement->passwd = malloc(sizeof(char)*strlen("root")))== NULL){
                    createErrorReport("Echec lors d'une allocation memoire)",__FILE__,__LINE__,__DATE__,__TIME__);
                    return 0;
                }
                if(strcpy(dbConfigElement->passwd,"root")==NULL){
                    createErrorReport("Echec lors de la copie d'une chaine de caractere",__FILE__,__LINE__,__DATE__,__TIME__);
                    return 0;
                }
            }
        }

        else if(strncmp(arrayParameters[counterParameters],"db=",strlen("db=")) == 0){            
            if((dbConfigElement->db = malloc(sizeof(char)*strlen(arrayParameters[counterParameters])- strlen("db=")))== NULL){
                createErrorReport("Echec lors d'une allocation memoire)",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;   
            }
            if(strcpy(dbConfigElement->db,(arrayParameters[counterParameters]+ strlen("db=")))==NULL){
                createErrorReport("Echec lors de la copie d'une chaine de caractere",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }

        else if(strncmp(arrayParameters[counterParameters],"playerLogin=",strlen("playerLogin=")) == 0){           
            if((dbConfigElement->playerLogin = malloc(sizeof(char)*strlen(arrayParameters[counterParameters])- strlen("playerLogin=")))== NULL){
                createErrorReport("Echec lors d'une allocation memoire)",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
            if(strcpy(dbConfigElement->playerLogin,(arrayParameters[counterParameters]+ strlen("playerLogin=")))==NULL){
                createErrorReport("Echec lors de la copie d'une chaine de caractere",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }

        else if(strncmp(arrayParameters[counterParameters],"playerPasswd=",strlen("playerPasswd=")) == 0){           
            if((dbConfigElement->playerPasswd = malloc(sizeof(char)*strlen(arrayParameters[counterParameters])- strlen("playerPasswd=")))== NULL){
                createErrorReport("Echec lors d'une allocation memoire)",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
            if(strcpy(dbConfigElement->playerPasswd,(arrayParameters[counterParameters]+ strlen("playerPasswd=")))==NULL){
                createErrorReport("Echec lors de la copie d'une chaine de caractere",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;    
            }
        }
        counterParameters++;
    }

    return 1;
}

FileIndex * initFileIndex(){

    FileIndex *fileIndex;

    if((fileIndex=malloc(sizeof(FileIndex)))==NULL){
        createErrorReport("Erreur d'alloctation memoire",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }

    if((fileIndex->err=returnFileElement("logs/errorLog.txt","a+"))==NULL){
        createErrorReport("Erreur lors de la creation d'un element fichier",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }
    fileIndex->err->filePointer=NULL;
    
    if((fileIndex->config=returnFileElement("conf/popTube.cfg","r+"))==NULL){
        createErrorReport("Erreur lors de la creation d'un element fichier",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }
    fileIndex->config->filePointer=NULL;

    if((fileIndex->metroLineColor=returnFileElement("txt/metroLineColors.txt","r"))==NULL){
        createErrorReport("Erreur lors de la creation d'un element fichier",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }

    fileIndex->metroLineColor->filePointer=NULL;

    return fileIndex;
}

File *returnFileElement(char *fullName, char* openMode  ){

    File *fileElement;

    if((fileElement=malloc(sizeof(File)))==NULL){
        createErrorReport("Echec lors d'une allocation memoire",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }

    if((fileElement->fullName=malloc(sizeof(char)*(strlen( fullName )+1 ) ) ) == NULL){
        createErrorReport("Echec lors d'une allocation memoire",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }
    if(strcpy(fileElement->fullName,fullName)==NULL){
        createErrorReport("Echec lors de la copie d'une chaine de caractere",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }
    if(strlen(openMode)>3){
        createErrorReport("Taille du mode d'ouverture trop importante",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }
    if(strcpy(fileElement->openMode,openMode)==NULL){
        createErrorReport("Echec lors de la copie d'une chaine de caractere",__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }
    return fileElement;
}

/*
* ─── FONCTIONS DE LIBERATION D'ALLOCATION ────────────────────────────────────────
*/

void freeFileIndex(FileIndex *fileIndex){

    freeFileElement(fileIndex->err);
    free(fileIndex->err);

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