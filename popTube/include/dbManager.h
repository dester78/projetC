#ifndef DBMANAGER
#define DBMANAGER
#include <mysql.h>
#include <structures.h>

//Crer une connection SQL represente par le pointeur *dbConnection, pour se connecter au serveur SQL les paramètres de *dbConfigElement sont indispensables
int createMysqlConnection(DbConfig *dbConfigElement, MYSQL *dbConnection);


#endif 