#include <structures.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void initDbConfig(DbConfig *newDbConfig, char ***arrayParameters){

    int counterParameters=0;
    
    while(strcmp(*(*arrayParameters+counterParameters),"\0")!=0){

        
        if(strncmp(*(*arrayParameters+counterParameters),"host=",strlen("host=")) == 0){

            newDbConfig->host = malloc(sizeof(char*)*strlen(*(*arrayParameters+counterParameters))- strlen("host="));

            if(newDbConfig->host != NULL){
                strcpy(newDbConfig->host,(*(*arrayParameters+counterParameters)+ strlen("host=")));
            }

            printf("%s",newDbConfig->host);
        }

        else if(strncmp(*(*arrayParameters+counterParameters),"user=",strlen("user=")) == 0){

            newDbConfig->user = malloc(sizeof(char*)*strlen(*(*arrayParameters+counterParameters))- strlen("user="));
            
            if(newDbConfig->user != NULL){
                strcpy(newDbConfig->user,(*(*arrayParameters+counterParameters)+ strlen("user=")));
            }
        }

        else if(strncmp(*(*arrayParameters+counterParameters),"passwd=",strlen("passwd=")) == 0){

            newDbConfig->passwd = malloc(sizeof(char*)*strlen(*(*arrayParameters+counterParameters))- strlen("passwd="));
            
            if(newDbConfig->passwd != NULL){
                strcpy(newDbConfig->passwd,(*(*arrayParameters+counterParameters)+ strlen("passwd=")));
            }
        }

        
        else if(strncmp(*(*arrayParameters+counterParameters),"db=",strlen("db=")) == 0){

            newDbConfig->db = malloc(sizeof(char*)*strlen(*(*arrayParameters+counterParameters))- strlen("db="));
            
            if(newDbConfig->db != NULL){
                strcpy(newDbConfig->db,(*(*arrayParameters+counterParameters)+ strlen("db=")));
            }
        }

        counterParameters++;
    }

}

