#ifndef DBMANAGER
#define DBMANAGER
#include <mysql.h>
#include <structures.h>


int createMysqlConnection(DbConfig *dbConfigElement, MYSQL *dbConnection);



#endif 