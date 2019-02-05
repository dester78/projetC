#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>

#include <dbManager.h>
#include <structures.h>
#include <fileManager.h>

#include <mysql.h>

/*
 * ─── FONCTIONS DE BASE DE DONNEE MYSQL ──────────────────────────────────────────
 */

short createMysqlConnection(DbConfig *dbConfigElement, MYSQL *dbConnection){


    if (mysql_init(dbConnection)==NULL){
        fprintf(stderr,"Echec lors de l'initialisation de connexion a la base de donnee dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,mysql_error(dbConnection));
        return 0; 
    }
    mysql_options(dbConnection,MYSQL_READ_DEFAULT_GROUP,"option");  
            
    if (mysql_real_connect(dbConnection,  dbConfigElement->host, dbConfigElement->user, dbConfigElement->passwd, dbConfigElement->db, 0, NULL, 0) == NULL){
        fprintf(stderr,"Echec lors de la connexion a la base de donnee dans le fichier %s ligne %d  (%s)\n",__FILE__,__LINE__,mysql_error(dbConnection));
        return 0; 
    }
    return 1;

}

