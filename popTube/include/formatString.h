#ifndef FORMATSTRING
#define FORMATSTRING


//Fonction traitant une chaine de caractère passée en paramètre et référencée par un pointeur,
//elle supprime le retour chariot de la chaine, ces traitements sont effectués en passant par une chaine de caractère intérmédiaire.
void deleteLineFeed( char **row  );

//Fonction traitant une chaine de caractère passée en paramètre et référencée par un pointeur,
//elle supprime les espaces de fin de chaine, ces traitements sont effectués en passant par une chaine de caractère intérmédiaire.
void deleteEndSpace(char **row  );

//Formate une chaine de caractère en détectant si c'est un chemin absolu avec le caractère :,
//si s'en est un la fonction rajoute un \ si il n'y en a pas en fin de chaine.
void formatFullPath(char ** fullPathString);

#endif