#include <stdio.h>
#include <stdlib.h>

#include <fileManager.h>
#include <structures.h> 
#include <dbManager.h>

#include <SDL2/SDL.h>
#include <mysql.h>




int main(int argc, char **argv) {
     
    char *configFileName="popTube.ini";
    char *openMode="r";
    FILE *configFile;
    MYSQL *dbConnection;
    DbConfig *dbConfigElement;
    int lastRow;
    int *arrayRowChar;
    char ***arrayParameters;
    SDLConfig *config;
    
    config=malloc(sizeof(SDLConfig*));
    config->video=(malloc(sizeof(SDLVideoConfig*)));

    // config->video->windowFlag=0x00000001;
    // config->video->windowFlag=config->video->windowFlag| 0x00000004 ;


    arrayParameters=malloc(sizeof(char***));

    dbConfigElement=malloc(sizeof(DbConfig*));

    if(dbConfigElement!=NULL){

        configFile=openFile(configFileName,openMode);
        arrayRowChar=countFileRowChar(configFile,&lastRow);
        returnFileParameters(configFile,arrayRowChar,arrayParameters ,lastRow);
        
        initDbConfig(dbConfigElement,arrayParameters);

        if((dbConnection=mysqlConnection(dbConfigElement))!=NULL){
            
        }

    }

    initSDLVideoConfig(config->video ,arrayParameters);



    if (SDL_Init(SDL_INIT_VIDEO ) != 0 ){
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    else{
        /* Création de la fenêtre */
        SDL_Window* mainWindow = NULL;
        mainWindow = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_UNDEFINED,
                                                                  SDL_WINDOWPOS_UNDEFINED,
                                                                  640,
                                                                  480,
                                                                  config->video->windowFlag);

        if( mainWindow )
        {
            SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voie la fenêtre */

            SDL_DestroyWindow(mainWindow);
        }
        else
        {
            fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        }
    }

    SDL_Quit();



    mysql_close(dbConnection);
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