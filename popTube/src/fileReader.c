#include <stdio.h>
#include <stdlib.h>
#include <structures.h>
#include <fileReader.h>
#include <string.h>


FILE *openFile(char *fileName, char *openMode){

    FILE *file;
    if(fileName!=NULL && openMode!=NULL){

        file=fopen(fileName,openMode);
        return file;
    }

    return NULL;

}


void initDbConfig(FILE *configFile, DbConfig *newDbConfig){

    int lastRow;
    int *arrayRowChar;
    char *fileRow; 
    char searchChar[2];
    int counterRow;

    arrayRowChar=countFileRowChar(configFile,&lastRow);

    
    for(counterRow=0;counterRow<lastRow;counterRow++){

        fileRow=malloc(sizeof(char)*(arrayRowChar[counterRow]+1));

        if(fileRow!=NULL){

            // printf("::::: %d ::::",arrayRowChar[counterRow]);
            //printf("position : %d",ftell(configFile));
            fgets(fileRow,arrayRowChar[counterRow]+1,configFile);
            //printf("%s : %d",fileRow,strlen(fileRow));


            //printf("position : %d caractere : %d \n",ftell(configFile),arrayRowChar[counterRow]);
            deleteEndRow(&fileRow);
            printf("%s",fileRow);
            //strncpy(searchChar,fileRow,1);
            // free(fileRow);
            // printf("%s",fileRow[0]);
    
            // if(strncmp(fileRow,"host=",strlen("host=")) == 0 && searchChar[0] != '#'){

            //     (*newDbConfig).host = malloc(sizeof(char) * (arrayRowChar[counterRow] - strlen("host=")));
            //     strcpy((*newDbConfig).host,(fileRow+strlen("host=")));

            // }

            // else if(strncmp(fileRow,"user=",strlen("user=")) == 0 && searchChar[0] != '#'){

            //     (*newDbConfig).user = malloc(sizeof(char) * (arrayRowChar[counterRow] - strlen("user=")));
            //     strcpy((*newDbConfig).user,(fileRow+strlen("user=")));

            // }

            // else if(strncmp(fileRow,"passwd=",strlen("passwd=")) == 0 && searchChar[0] != '#'){

            //     (*newDbConfig).passwd = malloc(sizeof(char) * (arrayRowChar[counterRow] - strlen("passwd=")));
            //     strcpy((*newDbConfig).passwd,(fileRow+strlen("passwd=")));

            // }

            // else if(strncmp(fileRow,"db=",strlen("db=")) == 0 && searchChar[0] != '#'){

            //     (*newDbConfig).db = malloc(sizeof(char) * (arrayRowChar[counterRow] - strlen("db=")));
            //     strcpy((*newDbConfig).db,(fileRow+strlen("db=")));

            // }
            
            // printf("caractere : %c",searchChar[0]);
            // printf("%d : %d : %s",counterRow,arrayRowChar[counterRow],fileRow);
            //printf("<<<<<<<<<<nbchar:%d nbrow: %d row: %s sizeRow: %d :>>>>>>>>>>>",arrayRowChar[counterRow], counterRow, fileRow,strlen(fileRow));
            free(fileRow);
        
        }
        
    }

    free(arrayRowChar);
}

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

                arrayRowChar=realloc(arrayRowChar,sizeof(int)*(counterRow+1));
                arrayRowChar[counterRow]=counterChar;
                counterChar=0;

                if(bufferChar==EOF){
                    counterChar=-1;
                }
                counterRow++;
            }

        }
    }
    
    fseek(file,0,SEEK_SET);
    *lastRow=counterRow;
    
    return arrayRowChar;

}

void deleteEndRow( char **row){

char *bufferRow;
int counterChar;
int sizeRow;


sizeRow=strlen(*row);

    if(*(*row+sizeRow-1)=='\n'){

        bufferRow=malloc(sizeof(char)*(sizeRow+1));

        strcpy(bufferRow,*row);

        free(row);

        *row=malloc(sizeof(char)*(sizeRow));

        for(counterChar=0;counterChar<sizeRow-1;counterChar++){
            *(*row+counterChar)=bufferRow[counterChar];
        }
        *(*row+counterChar)='\0';
        free(bufferRow);
        
    }
    

}




// void deleteEndRow( char *row){

// char *bufferRow;
// char *p;
// int counterChar;
// size_t sizeRow;

// // printf("%s",*row);
// //printf("%s",*row+1);
// sizeRow=strlen(row);



//     if(strcmp((row+strlen(row)-1),"\n")==0){

//         printf("too");
//     // counterChar=0;
//     // bufferRow=malloc(sizeof(char));

//     //     while(strcmp((*row+counterChar),"\n")!=0){

//     //         // p=*row+counterChar;
//     //         // counterChar--;
//     //         // printf("%s",bufferRow);
//     //         bufferRow=realloc(bufferRow,sizeof(char)*(counterChar+1));
//     //         bufferRow[counterChar]=*row+strlen((*row)-(counterChar+1));
//     //         counterChar++;

//     //         printf("%s",bufferRow);


//     //     }
//         //printf("%d\n",sizeRow);
//         // printf("%s \n",*row);
//         // printf("taille %d ",sizeof(char)*strlen(row));
//         //  printf("%s",row+sizeRow-1);
//         //  printf("%s",row);
//         // printf("%d : ",sizeRow);
//         bufferRow=malloc(sizeof(char)*(sizeRow+1));
//         // *(bufferRow)=*(row+1);
//         // *(bufferRow)=*(row+2);
//         strcpy(bufferRow,row);
//         free(row);

//         row=malloc(sizeof(char)*(sizeRow+2));
//         for(counterChar=0;counterChar<sizeRow-1;counterChar++){
//             row[counterChar]=bufferRow[counterChar];
//             // printf("%c",bufferRow[counterChar]);
//             printf("%c",row[counterChar]);
//         }
        
//         // printf(" %c \n", *(*(row+1)));
//         // printf(" %c \n",*(bufferRow+2));
//         // printf("%s",*row);
//         //free(row);
//         // free(row);
//         // printf("toto");

//         //row=malloc(sizeof(char)*(sizeRow+1));
//         // printf("%s",*row);
//         //counterChar=0;
//         // row=malloc(sizeof(char));
//         // printf("tutu");
//         //strcpy(row,*(bufferRow+1));
        
//         // printf("%s",row);


//         // while(*(bufferRow+counterChar)!='\n'){
//         //     // printf("%c",*(bufferRow+counterChar));
//         //     // row=realloc(row,sizeof(char)*counterChar);
//         //     // strcat(row,*(bufferRow+counterChar));
//         //     counterChar++;
//         // }
//         // printf("%d",strlen(row));



//         // free(*row);
//         // row=malloc(sizeof(char)*(sizeRow));
//         // strcpy(row,bufferRow);

//         // printf("%s",row);
//         // // printf("%d",sizeof(row));
//         // // printf("%d",sizeof(bufferRow));
//         // *row=(char*)malloc(sizeof(char*)*sizeRow);
//         // free(row);
//         // // row=malloc(sizeof(char*)*(sizeRow+1));
//         // printf("%d",strlen(bufferRow));
//         // printf("%s",bufferRow);

//         // // strncpy(row,bufferRow,sizeRow+1);
//         // free(row);
//         free(bufferRow);
//         // printf("%s",row);
        
//     }
    

// }







