#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>

#include <fileManager.h>
#include <structures.h> 
#include <dbManager.h>
#include <SDLMain.h>

#include <SDL.h>
// #include <SDL_ttf.h>
#include <mysql.h>

int main(int argc, char **argv) {
     
    char *configFileName="popTube.cfg";
    char openMode[3]="r";
    FILE *configFile;
    MYSQL dbConnection;
    
    int lastRow;
    int *arrayRowChar;
    
    char **arrayParameters;
    SDL_DisplayMode * arrayDisplayModes;
    SDLConfig SDLConfigElement;
    DbConfig dbConfigElement;
    SDL_Window* mainWindow;
    
    configFile=malloc(sizeof(FILE));
    

    if((configFile=openFile(configFileName,openMode))!=NULL){

        arrayRowChar=countFileRowChar(configFile,&lastRow);
        arrayParameters=returnFileParameters(configFile,arrayRowChar ,&lastRow);        
    }

    else{
        printf("Erreur lors du chargement du fichier %s", configFileName);
    }        

    

    if(initDbConfig(&dbConfigElement,arrayParameters,lastRow)){

        if(initSDLConfig(&SDLConfigElement,arrayParameters,lastRow)){

            
            
            if(createMysqlConnection(&dbConfigElement,&dbConnection)){
            
 
            }

            else{
                
            }
        }
    }
    

    if (SDL_Init( SDLConfigElement.init->initFlag ) != 0 ){
        printf("toto");
        fprintf(stderr,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    else{
        if((mainWindow=SDLCreateMainWindow(SDLConfigElement.window->windowFlag))!=NULL){


           arrayDisplayModes=SDLGetArrayDisplayModes();
           

        }
    }

    

    
    freeDbConfigElement(&dbConfigElement);
    freeSDLConfigElement(&SDLConfigElement);
    freeArrayParameter(arrayParameters,lastRow);
    
    free(arrayParameters);
    free(arrayDisplayModes);

    mysql_close(&dbConnection);
    SDL_Quit();
    mysql_library_end();

    free(configFile);
    return 0;

}



//     int status =  EXIT_FAILURE;

//     SDL_Event event; 

//     MYSQL *mysql;
//     /* Initialisation bibliotheque mysql */
//     if (mysql_library_init(0, NULL, NULL) == 0)
//     {
//         /* Initialisation du pointeur MYSQL */
//         mysql = mysql_init(NULL);
//         if (mysql != NULL)
//         {
//             fprintf(stdout, "[OK] mysql_init\n");
 
//             /* Connexion au serveur mysql */
//             if (mysql_real_connect(mysql, "localhost", "root", "root", "sys", 0, NULL, 0) != NULL)
//             {
//                 fprintf(stdout, "[OK] mysql_real_connect\n");
//             }
//             else
//             {
//                 fprintf(stderr, "[ERR] mysql_real_connect : '%s'\n", mysql_error(mysql));
//             }
 
//             /* Fermeture de la connexion / Liberation memoire mysql */
//             mysql_close(mysql);
//             mysql = NULL;
//         }
//         else
//         {
//             perror("mysql_init");
//         }
 
//         /* Fermeture de la bibliotheque */
//         mysql_library_end();
//     }
//     else
//     {
//         fprintf(stderr, "[ERR] mysql_library_init\n");
//     }
 
     
//     // Initialisation + vérification de la SDL : VIDEO.
//     i
    
// quit:
//     // Quitter SDL.
//     SDL_Quit();
     
//     return status;