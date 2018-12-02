#define ERROR_BUFFER_SIZE 250
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <structures.h>
#include <fileManager.h>
#include <formatString.h>




FILE *openFile(char *fileName, char *openMode){

    FILE *file;

    if((file=malloc(sizeof(FILE)))!=NULL){

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
    }
    return NULL;
}


FILE *openFluxFile(char *fileName, char *openMode){

    FILE * redirectFile; 

    if((redirectFile=malloc(sizeof(FILE)))!=NULL){

        if((redirectFile=freopen(fileName,openMode,stderr))!=NULL){
            return redirectFile;
        }

        else if((redirectFile=freopen(fileName,"w+",stderr))!=NULL){
            return redirectFile;
        }

        else{
            createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
            return NULL; 
        }
    }
    else{
        createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
        return NULL;
    }
}


void returnFileParameters(FILE *configFile, int *lastRow, char ***arrayParameters){

    char *fileRow; 
    int counterFileRow;
    int *arrayRowChar;
    char commentChar[2];
    int counterParameters=0;

    if((*arrayParameters=malloc(sizeof(char*)*(countFileRowChar(&arrayRowChar,configFile,lastRow))))!=NULL){

        for(counterFileRow=0;counterFileRow<*lastRow;counterFileRow++){
            
            if((fileRow=malloc(sizeof(char)*(arrayRowChar[counterFileRow]+1)))!=NULL){

                if(arrayRowChar[counterFileRow]!=-1){
                    
                    if(arrayRowChar[counterFileRow]<=1&&arrayRowChar[counterFileRow]<*lastRow-1){   //Utile dans le cas d'une ligne composé seulement d'un \n
                        fseek(configFile,2,SEEK_CUR);
                    }
                    else{
                        fgets(fileRow,arrayRowChar[counterFileRow]+1,configFile);
                        strncpy(commentChar,fileRow,1);

                        if(commentChar[0]!='#'){
                            
                            deleteLineFeed(&fileRow);
                            deleteEndSpace(&fileRow);

                            // if((*arrayParameters=realloc(*arrayParameters,(sizeof(char*)*(counterParameters+1))))!=NULL){

                                if(((*arrayParameters)[counterParameters]=malloc(sizeof(char)*( arrayRowChar[counterFileRow]+1) ))!=NULL){

                                    strncpy( (*arrayParameters)[counterParameters],fileRow,(arrayRowChar[counterFileRow])); 
                                    printf("%d",strlen((*arrayParameters)[counterParameters]));
                                    printf("%s|",(*arrayParameters)[counterParameters]);
                                }  
                                else{createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);}
                            // } 
                            // else{createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);} 

                        counterParameters++;              
                        }  

                    }
                       
                }
                free(fileRow);
                fileRow=NULL;
            }
            else{createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
            }
        }       
    }
    else{createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);}

    free(arrayRowChar);

    *lastRow=counterParameters;

}

//Fonction parcourant un fichier passé en paramètre afin de compter le nombres de lignes et le nombre de caractères/ligne. Renvoie ensuite un tableau contenant ces informations.
int countFileRowChar(int **arrayRowChar,FILE *file, int *lastRow){

    int counterRow=0; 
    int counterParameters=0;
    char bufferChar;
    int counterChar=0;

    fseek(file,0,SEEK_SET);
    
    if((*arrayRowChar=malloc(sizeof(int)))!=NULL){

        while(counterChar!=-1){

            bufferChar=fgetc(file);
            counterChar++;

            if(bufferChar=='#'){
                counterParameters++;
            }
               
            if(bufferChar=='\n'||bufferChar==EOF){

                *arrayRowChar=realloc(*arrayRowChar,sizeof(int)*(counterRow+1));
                (*arrayRowChar)[counterRow]=counterChar;
                
                if(bufferChar==EOF){
                    counterChar=-1;
                }
                else{counterChar=0;}

                counterRow++;
            }
        }
        fseek(file,0,SEEK_SET);
        *lastRow=counterRow;
    }        

    else{
        createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
    }  

    return counterParameters; 
}

void freeCharArray(char*** arrayChar, int lastRow ){

    int counter=0;
    
    while(counter<lastRow){
        free((*arrayChar)[counter]);
        (*arrayChar)[counter]=NULL;
        counter++;
    }

    free(*arrayChar);
}


// void freeIntArray(int** intArray, int lastRow){

//     int counter=0;

//     printf("%d",intArray[0]);
//     printf("%d",lastRow);
//     while(counter<lastRow){

//         free(intArray[counter]);
//         intArray[counter]=NULL;
//         counter++;
//     }
//     printf("toto");
// }


void createErrorReport(char * fileError, int lineError, char  *dateError, char *timeError){

    char  errorReportString[ERROR_BUFFER_SIZE]; 

    if(sprintf(errorReportString,"| Error | file %s | line %d | date %s | time %s |",fileError,lineError,dateError,timeError)>0){
        
        perror(errorReportString);
    }

    else{fprintf(stderr,"Erreur lors de la création d'un message d'erreur dans la fonction %s",__func__);}
}




