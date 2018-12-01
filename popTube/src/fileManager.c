#define ERROR_BUFFER_SIZE 250
#include <stdio.h>
#include <stdlib.h>
#include <structures.h>
#include <fileManager.h>
#include <string.h>



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


char **returnFileParameters(FILE *configFile,  int *arrayRowChar, int *lastRow ){

    char *fileRow; 
    int counterFileRow;
    char commentChar[2];
    int counterParameters=0;
    char **arrayParameters;

    if((arrayParameters=malloc(sizeof(char*)))!=NULL){

        for(counterFileRow=0;counterFileRow<*lastRow;counterFileRow++){

            if((fileRow=malloc(sizeof(char)*(arrayRowChar[counterFileRow]+1)))!=NULL){

                if(arrayRowChar[counterFileRow]!=-1){
                    
                    fgets(fileRow,arrayRowChar[counterFileRow]+1,configFile);
                    strncpy(commentChar,fileRow,1);
 
                    if(commentChar[0]!='#' && commentChar[0]!='\n' && commentChar[0]!=EOF && commentChar[0]!='\0'){
                        
                        deleteLineFeed(&fileRow);
                        deleteEndSpace(&fileRow);

                        if((arrayParameters=realloc(arrayParameters,(sizeof(char*)*(counterParameters+1))))!=NULL){

                            if((arrayParameters[counterParameters]=malloc(sizeof(char)*( arrayRowChar[counterFileRow]) ))!=NULL){

                                strncpy( arrayParameters[counterParameters],fileRow,(arrayRowChar[counterFileRow])); 
                                printf("%s",arrayParameters[counterParameters]);
                            }  
                            else{createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);}
                        } 
                        else{createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);} 

                    counterParameters++;              
                    }     
                }
                free(fileRow);
            }
            else{createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
            }
        }       
    }
    else{createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);}

    *lastRow=counterParameters;
    return arrayParameters;
}

//Fonction parcourant un fichier passé en paramètre afin de compter le nombres de lignes et le nombre de caractères/ligne. Renvoie ensuite un tableau contenant ces informations.
int *countFileRowChar(FILE *file, int *lastRow){

    int counterRow=0; 
    int *arrayRowChar;
    char bufferChar;
    int counterChar=0;

    fseek(file,0,SEEK_SET);
    
    if((arrayRowChar=malloc(sizeof(int)))!=NULL){

        while(counterChar!=-1){

            bufferChar=fgetc(file);
            counterChar++;

            if(bufferChar=='\n'||bufferChar==EOF){

                arrayRowChar=realloc(arrayRowChar,sizeof(int)*(counterRow+1));
                arrayRowChar[counterRow]=counterChar;
                
                if(bufferChar==EOF){
                    counterChar=-1;
                }
                else{counterChar=0;}

                counterRow++;
            }
        }
        fseek(file,0,SEEK_SET);
        *lastRow=counterRow;
        return arrayRowChar;
    }        

    else{
        createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
        return 0;
    }   
}

void deleteLineFeed( char **row ){

char *bufferRow;
int counterChar;
int sizeRow;

sizeRow=strlen(*row);

    if(*(*row+sizeRow-1)=='\n'&& *(*row+sizeRow)!=EOF){

        if((bufferRow=malloc(sizeof(char)*(sizeRow+1)))!=NULL){

            strcpy(bufferRow,*row);
            free(*row);

            if((*row=malloc(sizeof(char)*(sizeRow)))!=NULL){

                for(counterChar=0;counterChar<sizeRow-1;counterChar++){
                    *(*row+counterChar)=bufferRow[counterChar];
                }
                *(*row+counterChar)='\0';
            }

            else{createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);}
            
            free(bufferRow);
            bufferRow=NULL;
        }
        else{createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);}
    }
}

void deleteEndSpace(char **row ){

char *bufferRow;
int counterChar;
int counterSpace=0;
int sizeRow;

sizeRow=strlen(*row);
    
    if((bufferRow=malloc(sizeof(char)*(sizeRow+1)))!=NULL){

        strcpy(bufferRow,*row);
        if(bufferRow[sizeRow-1]==' '){
    
            free(*row);
            counterChar=sizeRow-1;
            while(bufferRow[counterChar-counterSpace]==' '){
                counterSpace++;
            }

            if((*row=malloc(sizeof(char)*(sizeRow-counterSpace)))!=NULL){

                for(counterChar=0;counterChar<(sizeRow-counterSpace);counterChar++){

                    *(*row+counterChar)=bufferRow[counterChar];
                }
                *(*row+counterChar)='\0';
            }

            else{createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);}
        }
        free(bufferRow);
    }
    else{createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);}
}


void freeArrayParameter(char** arrayParameters, int lastRow ){

    int counterParameters=0;
    
    while(counterParameters<lastRow){

        free(arrayParameters[counterParameters]);
        arrayParameters[counterParameters]=NULL;
        counterParameters++;
    }
}


void createErrorReport(char * fileError, int lineError, char  *dateError, char *timeError){

    char  errorReportString[ERROR_BUFFER_SIZE]; 

    if(sprintf(errorReportString,"| Error | file %s | line %d | date %s | time %s |",fileError,lineError,dateError,timeError)>0){
        
        perror(errorReportString);
    }

    else{fprintf(stderr,"Erreur lors de la création d'un message d'erreur dans la fonction %s",__func__);}
}







