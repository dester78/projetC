#define ERROR_BUFFER_SIZE 250
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <formatString.h>
#include <fileManager.h>

/*
 * ─── FONCTIONS DE FORMATAGE DE CHAINES DE CARACTERES ───────────────────────────
 */

short deleteLineFeed( char **row ){

    int sizeRow;

    if((sizeRow=strlen(*row))==0){
        createErrorReport("La chaine de caractere est vide",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;
    }
    if((*row)[sizeRow-1]=='\n' && (*row)[sizeRow-1]!=EOF ){
        
        (*row)[sizeRow-1]='\0';
    }
    
    return 1;
}

short deleteEndSpace(char **row ){

    int counterChar;
    int counterSpace=0;
    int sizeRow;

    if((sizeRow=strlen(*row))==0){
        createErrorReport("La chaine de caractere est vide",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;
    }

    counterChar=sizeRow-1;

    while((*row)[counterChar-counterSpace]==' '){
        (*row)[counterChar-counterSpace]='\0';
        counterSpace++;
    }
    return 1;
}

short extractWindowDimensionsFromString(char *string, int *dimension){

    char stringDimension[5];
    unsigned char  counterCharNumber=0;
    errno=0;
    
    for(unsigned char counterChar=0; counterChar<strlen(string);counterChar++){

        if(string[counterChar]>=48&&string[counterChar]<=57){
            counterCharNumber++;
        }
        else if((string[counterChar]<48||string[counterChar]>57)&&counterCharNumber!=0){
            
            if(strncpy(stringDimension,string+(counterChar-counterCharNumber),counterCharNumber)==NULL){
                createErrorReport("La copie de la chaine de caractere n'a pas fonctionne",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
            stringDimension[4]='\0';

            counterCharNumber=0;

            if(dimension[0]==0){
                dimension[0]=atoi(stringDimension);//Stock la largeur
            }
            else{
                dimension[1]=atoi(stringDimension);//Stock la hauteur
            }
            if(errno==ERANGE){
                createErrorReport("La taille de la fenetre du fichier de configuration depasse les valeurs admise par ce programme",__FILE__,__LINE__,__DATE__,__TIME__);
                return 0;
            }
        }
    }
    return 1;
}

short formatFullPath(char ** fullPathString){

    int sizeString;

    if((sizeString=strlen(*fullPathString))==0){
        createErrorReport("Le chemin absolue n'est pas un chemin valide",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;
    }

    //Cherche le caractère : afin de déterminer si le chemin est bien un chemin absolue
    if(strchr(*fullPathString,':')!=NULL){

        if((*fullPathString)[sizeString-1]!='\\'){
            (*fullPathString)[sizeString]='\\';
            (*fullPathString)[sizeString+1]='\0';
        }
    }

    else{
        createErrorReport("Le chemin absolue n'est pas un chemin valide",__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;
    }
    return 1;
}

