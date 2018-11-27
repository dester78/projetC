#include <stdio.h>
#include <stdlib.h>
#include <structures.h>
#include <fileManager.h>
#include <string.h>


FILE *openFile(char *fileName, char *openMode){

    FILE *file;
    file=malloc(sizeof(FILE));

    
    if((file=fopen(fileName,openMode))!=NULL){
        
        return file;
    }
        
    

    else{
        printf("Erreur lors de l'allocation du pointeur de fichier dans la fonction %s",__func__);
        return NULL;
    }
}

//Fonction parcourant un fichier afin de créer un tabeau de paramètres nécessaire au fonctionnement du programme 
void returnFileParameters(FILE *configFile,int *arrayRowChar, char ***arrayParameters, int lastRow){

    char *fileRow; 
    int counterFileRow;
    char commentChar[2];
    int counterParameters=0;


        for(counterFileRow=0;counterFileRow<lastRow;counterFileRow++){

            fileRow=malloc(sizeof(char*)*(arrayRowChar[counterFileRow]+1));

            if(fileRow!=NULL){

                if(counterFileRow==lastRow-1){
                    fgets(fileRow,arrayRowChar[counterFileRow]-1,configFile);
                }

                else{
                    fgets(fileRow,arrayRowChar[counterFileRow]+1,configFile);
                } 

                strncpy(commentChar,fileRow,1);

                if(commentChar[0]!='#'){
                    
                     
                    deleteLineFeed(&fileRow);
                    deleteEndSpace(&fileRow);
                    *arrayParameters=realloc(*arrayParameters,(sizeof(char**)*(counterParameters+1)));

                    if(*arrayParameters!=NULL){

                        *(*arrayParameters+counterParameters)=malloc(sizeof(char)*(arrayRowChar[counterFileRow]+1));
                        
                        if(*(*arrayParameters+counterParameters)!=NULL){

                            strcpy(*(*arrayParameters+counterParameters),fileRow); 
                            printf("%s\n",*(*arrayParameters+counterParameters));     
                        }  
                        else{
                            printf("Erreur lors de la modification d'une chaine de caractere du tableau de parametre dans la fonction %s",__func__);
                        }
                    } 
                    else{
                        printf("Echec lors de l'allocation de arrayParamaters dans la fonction %s",__func__);
                    } 

                    counterParameters++;              
                }
                free(fileRow);
            }
            else{
                printf("L'allocation du pointeur fileRow de la fonction %s n'a pas fonctionne",__func__);
            }
        }       
    
    *(*arrayParameters+counterParameters)=NULL;
}

//Fonction parcourant un fichier passé en paramètre afin de compter le nombres de lignes et le nombre de caractères/ligne. Renvoie ensuite un tableau contenant ces informations.
int *countFileRowChar(FILE *file, int *lastRow){

    int counterRow=0; 
    int *arrayRowChar;
    char bufferChar;
    int counterChar=0;

    fseek(file,0,SEEK_SET);
    arrayRowChar=malloc(sizeof(int));
    
    if(arrayRowChar!=NULL){

        while(counterChar!=-1){

            bufferChar=fgetc(file);
            counterChar++;

            if(bufferChar=='\n'||bufferChar==EOF){

                if(counterChar==1){
                    counterChar++;
                }

                arrayRowChar=realloc(arrayRowChar,sizeof(int)*(counterRow+1));
                arrayRowChar[counterRow]=counterChar;
                counterChar=0;

                if(bufferChar==EOF){
                    counterChar=-1;
                }
                counterRow++;
            }
        }

        fseek(file,0,SEEK_SET);
        *lastRow=counterRow;
        return arrayRowChar;
    }  
        

    else{
        printf("Echec lors de l'allocation du tableau arrayRowChar de la fonction %s",__func__);
        return 0;
    }
    
}

//Fonction supprimant le retour chariot de fin de chaine de caractères passée en paramètre en passant par un buffer pour faire les modifications nécessaires
void deleteLineFeed( char **row){

char *bufferRow;
int counterChar;
int sizeRow;

sizeRow=strlen(*row);

    if(*(*row+sizeRow-1)=='\n'&& *(*row+sizeRow)!=EOF){

        bufferRow=malloc(sizeof(char)*(sizeRow+1));
        if(bufferRow!=NULL){

            strcpy(bufferRow,*row);
            free(row);

            *row=malloc(sizeof(char)*(sizeRow));

            if(*row!=NULL){

                for(counterChar=0;counterChar<sizeRow-1;counterChar++){
                    *(*row+counterChar)=bufferRow[counterChar];
                }

            *(*row+counterChar)='\0';
            }

            else{
                printf("L'allocation du pointeur row de la fonction %s n'a pas fonctionné",__func__);
            }
            
            free(bufferRow);

        }
        else{
            printf("L'allocation du buffer de la fonction %s n'a pas fonctionné",__func__);
        }
    }
}

//Fonction supprimant les espaces présents à la fin d'une chaine de caractère passée en paramètre
void deleteEndSpace(char **row){

char *bufferRow;
int counterChar;
int counterSpace=0;
int sizeRow;

sizeRow=strlen(*row);

    bufferRow=malloc(sizeof(char)*(sizeRow+1));
    
    if(bufferRow!=NULL){

        strcpy(bufferRow,*row);
        if(bufferRow[sizeRow-1]==' '){
    
            free(row);
            counterChar=sizeRow-1;
            while(bufferRow[counterChar-counterSpace]==' '){
                counterSpace++;
            }

            *row=malloc(sizeof(char)*(sizeRow-counterSpace));

            if(*row!=NULL){

                for(counterChar=0;counterChar<(sizeRow-counterSpace);counterChar++){

                    *(*row+counterChar)=bufferRow[counterChar];
                }

                *(*row+counterChar)='\0';
            }

            else{
                printf("L'allocation du pointeur row de la fonction %s n'a pas fonctionné",__func__);
            }
        }

        free(bufferRow);
    }

    else{
        printf("L'allocation du pointeur bufferRow de la fonction %s n'a pas fonctionné",__func__);
    }
    
    
}







