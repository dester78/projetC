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
    char *openMode="r";
    FILE *configFile;
    MYSQL dbConnection;
    DbConfig *dbConfigElement;
    int lastRow;
    int *arrayRowChar;
    
    char **arrayParameters;
    SDLConfig *SDLConfigElement;
    SDL_Window* mainWindow;
    
    configFile=malloc(sizeof(FILE));
    SDLConfigElement=malloc(sizeof(SDLConfig));
    arrayParameters=malloc(sizeof(char**));
    dbConfigElement=malloc(sizeof(DbConfig));
    // dbConnection=malloc(sizeof(MYSQL));

    // mysql_library_init(0,NULL,NULL);

    printf("ta");
    
    if(dbConfigElement!=NULL){

        if((configFile=openFile(configFileName,openMode))!=NULL){

            
            arrayRowChar=countFileRowChar(configFile,&lastRow);
            returnFileParameters(configFile,arrayRowChar,&arrayParameters ,lastRow);
        }

        else{
            printf("Erreur lors du chargement du fichier %s", configFileName);
        }

        
        // initDbConfig(dbConfigElement,&arrayParameters);
        initSDLConfig(SDLConfigElement,&arrayParameters);

        // // if((dbConnection=mysqlConnection(dbConfigElement))!=NULL){
            
        // // }
        // printf("tete");


    }
    printf("%s",mysql_get_client_info());

    
    if(mysql_init(&dbConnection)!=NULL){

         mysql_options(&dbConnection,MYSQL_READ_DEFAULT_GROUP,"option");
            fprintf(stdout, "[OK] mysql_init\n");

            if (mysql_real_connect(&dbConnection,  "localhost", "root", "root", "sys", 0, NULL, 0) != NULL){
                fprintf(stdout, "[OK] mysql_real_connect\n");
                fprintf(stdout, "[ERR] mysql_real_connect : '%s'\n", mysql_error(&dbConnection));
                printf("toto");
                mysql_close(&dbConnection);

            }

            else{
                fprintf(stderr, "[ERR] mysql_real_connect : '%s'\n", mysql_error(&dbConnection));
            }
    }
    
 
        

        



    // if (SDL_Init(SDLConfigElement->init->initFlag ) != 0 ){
    //     fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
    //     return -1;
    // }

    // else{
    //     if((mainWindow=SDLCreateMainWindow(SDLConfigElement))!=NULL){

    //         SDLMainLoop(mainWindow);
    //     }
    // }

    // SDL_Quit();


    mysql_library_end();
    free(dbConfigElement);
    free(SDLConfigElement);
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