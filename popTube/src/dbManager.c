#include <stdio.h>

#include <winsock.h>
#include <dbManager.h>
#include <structures.h>

#include <mysql.h>


void mysqlConnection(DbConfig *dbConfigElement, MYSQL *dbConnection){

    
        if (dbConnection != NULL){

            fprintf(stdout, "[OK] mysql_init\n");

            if (mysql_real_connect(dbConnection,  dbConfigElement->host, dbConfigElement->user, dbConfigElement->passwd, dbConfigElement->db, 0, NULL, 0) != NULL){
                fprintf(stdout, "[OK] mysql_real_connect\n");
                mysql_close(dbConnection);
            }

            else{
                fprintf(stderr, "[ERR] mysql_real_connect : '%s'\n", mysql_error(dbConnection));
            }
 
        }

        else{
            perror("mysql_init");
        }
    

}