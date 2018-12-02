#ifndef FILEMANAGER
#define FILEMANAGER
#include <structures.h>
#include <stdio.h>


//Fonction permettant d'ouvrir un fichier, en fonction de son nom complet, et son mode d'ouverture, 
//si le mode d'ouverture n'est pas spécifié alors il sera ouvert en w+ par défaut.
FILE *openFile(char *fileName, char *openMode);

//Fonction permettant d'ouvrir un fichier, en fonction de son nom complet, et son mode d'ouverture, 
//si le mode d'ouverture n'est pas spécifié alors il sera ouvert en w+ par défaut. 
//Elle a pour rôle supplémentaire de redirigé un flux vers le fichier ouvert, par défaut stderr.
FILE *openFluxFile(char *fileName, char *openMode);

//Fonction renvoyant un tableau de chaines de caractères, ce tableau stock seulement les chaines correspondant à des paramètres. 
//Elle prend en paramètre un pointeur du fichier qui sera parcouru, un tableau contenant les informations de tailles du fichier (nb lignes / nb caractères)
//et la longueur du dit tableau. 
void returnFileParameters(FILE *configFile, int *lastRow,char ***arrayParameters );

//Fonction renvoyant un tableau contenant les informations de tailles d'un fichier (nb lignes / nb caractères), le pointeur FILE* passé en paramètre permet le parcours de ce fichier, 
//le second paramètre est un pointeur permettant de récupérer la longueur du tableau. La valeur de retour est le nombre de paramètres présents dans le fichier.
int countFileRowChar(int **arrayRowChar,FILE *file, int *lastRow);

//Fonction créant un message d'erreur comprenant, le fichier, la ligne, la date et l'heure de l'erreur, 
//ce message est ensuite envoyé dans le flux d'erreur avec la fonction perror
void createErrorReport(char *fileError, int lineError, char  *dateError, char *timeError);

//Fonction de libération d'allocation mémoire pour le tableau de paramètre
void freeCharArray(char*** charArray, int lastRow );
void freeIntArray(int** intArray, int lastRow);

#endif