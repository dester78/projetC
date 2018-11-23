#include <stdio.h>
#include <stdlib.h>
#include <fileReader.h>
#include <structures.h>  
#include <SDL2/SDL.h>
#include <mysql.h>



int main(int argc, char *argv[]) {
     
    char *configFileName="popTube.ini";
    char *openMode="r";
    FILE *configFile;
    DbConfig *newDbConfig;
    int lastRow;
    int *arrayRowChar;
    char ***arrayParameters;

    arrayParameters=malloc(sizeof(char***));

    newDbConfig=malloc(sizeof(DbConfig*));

    if(newDbConfig!=NULL){

        configFile=openFile(configFileName,openMode);
        arrayRowChar=countFileRowChar(configFile,&lastRow);
        returnFileParameters(configFile,arrayRowChar,arrayParameters ,lastRow);
        
        initDbConfig(newDbConfig,arrayParameters);

        printf("%s",newDbConfig->host);

    }


    MYSQL *mysql;
    /* Initialisation bibliotheque mysql */
    if (mysql_library_init(0, NULL, NULL) == 0)
    {
        /* Initialisation du pointeur MYSQL */
        mysql = mysql_init(NULL);
        if (mysql != NULL)
        {
            fprintf(stdout, "[OK] mysql_init\n");
 
            /* Connexion au serveur mysql */
            if (mysql_real_connect(mysql, newDbConfig->host, newDbConfig->user, newDbConfig->passwd, newDbConfig->db, 0, NULL, 0) != NULL)
            {
                fprintf(stdout, "[OK] mysql_real_connect\n");
            }
            else
            {
                fprintf(stderr, "[ERR] mysql_real_connect : '%s'\n", mysql_error(mysql));
            }
 
            /* Fermeture de la connexion / Liberation memoire mysql */
            mysql_close(mysql);
            mysql = NULL;
        }
        else
        {
            perror("mysql_init");
        }
 
        /* Fermeture de la bibliotheque */
        mysql_library_end();
    }
    else
    {
        fprintf(stderr, "[ERR] mysql_library_init\n");
    }
 
    free(newDbConfig);
    return 0;

}



//     int status =  EXIT_FAILURE;
    
//     SDL_Window *fenetre = NULL;
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
//     if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
//         fprintf(stdout,"Échec de l'initialisation de la SDL : %s\n", SDL_GetError());
//         goto quit;
//     }
     
//     // Création fenêtre.
//     fenetre = SDL_CreateWindow("Tuto SDL 2.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
//     if(fenetre == NULL) {
//         fprintf(stderr, "Impossible de créer la fenêtre : %s\n", SDL_GetError());
//         goto quit;
//     }
    
//     do {
//         SDL_WaitEvent(&event);
//     }
//     while(event.type != SDL_QUIT);
//     SDL_DestroyWindow(fenetre); 
//     status = EXIT_SUCCESS;
    
// quit:
//     // Quitter SDL.
//     SDL_Quit();
     
//     return status;