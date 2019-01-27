#define ERROR_BUFFER_SIZE 250
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDLColor.h>
#include <structures.h>
#include <fileManager.h>
#include <formatString.h>
#include <SDL.h>




FILE *openFile(char *fileName, char *openMode){

    FILE *file;

    printf("%s",openMode);

    if((file=fopen(fileName,openMode))!=NULL){
        return file;
    }
        
    else if((file=fopen(fileName,"w+"))!=NULL){
        return file;
    }

    else{
        createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }

    return NULL;
}


FILE *openFluxFile(char *fileName, char *openMode){

    FILE * redirectFile; 

    if((redirectFile=freopen(fileName,openMode,stderr))!=NULL){//freopen permet de rediriger un flux vers un fichier dans ce cas
        return redirectFile;
    }

    else if((redirectFile=freopen(fileName,"w+",stderr))!=NULL){//Si ca ne fonctionne pas le mode w+ permet de créer le fichier 
        return redirectFile;
    }

    else{
        createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL; 
    }

    return NULL;
}


void returnConfigFileParameters(FILE *configFile, int *lastRow, char ***arrayParameters){

    char *fileRow; 
    int counterFileRow;
    int *arrayRowChar;
    char commentChar[2];
    int counterParameters=0;
    int sizeArrayParameters=countFileRowChar(&arrayRowChar,configFile,lastRow);

    if(((*arrayParameters)=malloc(sizeof(char*)*sizeArrayParameters))!=NULL){

        for(counterFileRow=0;counterFileRow<*lastRow;counterFileRow++){
   
            if((fileRow=calloc(((arrayRowChar[counterFileRow])+1),sizeof(char)))!=NULL){
                
                if(arrayRowChar[counterFileRow]!=-1){
                    
                    if(arrayRowChar[counterFileRow] <= 1 && arrayRowChar[counterFileRow] < *lastRow - 1){   //Utile dans le cas d'une ligne compose seulement d'un \n
                        fseek(configFile,2,SEEK_CUR);//Déplace le curseur de fichier de 2 caractère en partant de sa position courante, utilisé pour sauté les lignes vides
                    }
                    else{
                        fgets(fileRow,arrayRowChar[counterFileRow]+1,configFile);//Lit une ligne du fichier et déplace le curseur automatiquement
                        strncpy(commentChar,fileRow,1);

                        if(commentChar[0]!='#'){//Vérifie si la ligne correspond à un paramètre ou un commentaire
                            
                            deleteLineFeed(&fileRow);
                            deleteEndSpace(&fileRow);
                            

                            if(((*arrayParameters)[counterParameters] = malloc( sizeof( char ) * ( strlen( fileRow ) + 1) ))!=NULL){
                                strcpy( (*arrayParameters)[counterParameters],fileRow); //Copie la ligne de paramètre dans le tableau de lignes de paramètre
                            }  
                            else{createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);}

                        counterParameters++;              
                        }  
                    }   
                }

                free(fileRow);//Désalloue la ligne
            }
            else{createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
            }
        }       
    }
    else{createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);}

    free(arrayRowChar);

    *lastRow=counterParameters;
}


void loadMetroLineColor(FILE *filePointer, char *city, SDL_Color **arrColors, unsigned short *sizeArrColor){

    char tmpCity[20];
    int r,g,b;

    fscanf(filePointer,"%s",tmpCity);
    if(strncmp(city,tmpCity,strlen(city))==0){
        while(fscanf(filePointer,"%d %d %d",&r,&g,&b),feof(filePointer)==0){
            (*sizeArrColor)++;
            (*arrColors)=realloc((*arrColors), *sizeArrColor*sizeof(SDL_Color));
            (*arrColors)[*sizeArrColor-1]=SDLChangeRGBColor(r,g,b,255);
        }

    }
}

//Fonction parcourant un fichier passe en paramètre afin de compter le nombres de lignes et le nombre de caractères/ligne. Renvoie ensuite un tableau contenant ces informations.
int countFileRowChar(int **arrayRowChar,FILE *file, int *lastRow){

    int counterRow=0; 
    int counterParameters=0;
    char bufferChar;
    int counterChar=0;

    fseek(file,0,SEEK_SET);//Place le curseur en début de fichier
    
    if((*arrayRowChar=malloc(sizeof(int)))!=NULL){

        while(counterChar!=-1){

            bufferChar=fgetc(file);//Lit le fichier caractère par caractère
            counterChar++;

            if(bufferChar=='#'){
                counterParameters++;
            }
               
            if(bufferChar=='\n'||bufferChar==EOF){

                *arrayRowChar=realloc(*arrayRowChar,sizeof(int)*(counterRow+1));//Réalloue le tableau à chaque nouvelle ligne
                (*arrayRowChar)[counterRow]=counterChar;
                
                if(bufferChar==EOF){//Stop la boucle quand le curseur arrive à la fin du fichier
                    counterChar=-1;
                }
                else{counterChar=0;}

                counterRow++;
            }
        }
        fseek(file,0,SEEK_SET);//Replace le curseur en début de fichier
        *lastRow=counterRow;
    }        

    else{
        createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
    }  

    return counterParameters; 
}

void freeCharArray(char*** arrayChar, int lastRow ){//Libère un tableau à deux dimension comprenant des chaines de caractères

    int counter=0;

    while(counter<lastRow){
        
        free((*arrayChar)[counter]);
        counter++;
    }
    free(*arrayChar);
}



void createErrorReport(char * fileError, int lineError, char  *dateError, char *timeError){

    char  errorReportString[ERROR_BUFFER_SIZE]; 

    if(sprintf(errorReportString,"| Error | file %s | line %d | date %s | time %s |",fileError,lineError,dateError,timeError)>0){
        
        perror(errorReportString);//Perror permet l'envoie d'une erreur dans le flux stderr, le message d'erreur comprend le fichier, la ligne, la date et l'heure de l'erreur
    }

    else{fprintf(stderr,"Erreur lors de la creation d'un message d'erreur dans la fonction %s",__func__);}
}




