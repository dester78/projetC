#ifndef FORMATSTRING
#define FORMATSTRING

/*
 * ─── FONCTIONS DE FORMATAGE DE CHAINES DE CARACTERES ───────────────────────────
 */

//Fonction traitant une chaine de caractère passée en paramètre sous forme de double pointeur elle supprime le retour chariot de la chaine.
short deleteLineFeed( char **row  );

//Fonction traitant une chaine de caractère passée en paramètre sous forme d'un double pointeur elle supprime les espaces de fin de chaine
short deleteEndSpace(char **row  );

//Formate une chaine de caractère en detectant si c'est un chemin absolu avec le caractère ":", si s'en est un la fonction rajoute un "\" si il n'y en a pas en fin de chaine.
short formatFullPath(char ** fullPathString);

//Récupère les dimensions de la fenêtre si elle est fournie en paramètre du fichier de configuration
short extractWindowDimensionsFromString(char *string, int *dimension);

#endif