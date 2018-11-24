#ifndef DBMANAGER
#define DBMANAGER
#include <mysql.h>
#include <structures.h>


MYSQL *mysqlConnection(DbConfig *dbConfigElement);



#endif 