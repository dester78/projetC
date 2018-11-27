#ifndef DBMANAGER
#define DBMANAGER
#include <mysql.h>
#include <structures.h>


void mysqlConnection(DbConfig *dbConfigElement, MYSQL *dbConnection);



#endif 