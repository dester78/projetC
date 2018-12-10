#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>

#include <dbManager.h>
#include <structures.h>
#include <fileManager.h>

#include <mysql.h>


int createMysqlConnection(DbConfig *dbConfigElement, MYSQL *dbConnection){


    if (mysql_init(dbConnection)!=NULL){

        mysql_options(dbConnection,MYSQL_READ_DEFAULT_GROUP,"option");       
        
        fprintf(stdout, "[OK] mysql_init\n");

        if (mysql_real_connect(dbConnection,  dbConfigElement->host, dbConfigElement->user, dbConfigElement->passwd, dbConfigElement->db, 0, NULL, 0) != NULL){
            fprintf(stdout, "[OK] mysql_real_connect\n");
            return 1;
            
        }

        else{
            perror(mysql_error(dbConnection));
            return 0;
        }
    }

    else{
        createErrorReport(__FILE__,__LINE__,__DATE__,__TIME__);
        return -1;
    }

}