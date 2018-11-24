#include <stdio.h>

#include <dbManager.h>
#include <structures.h>

#include <mysql.h>


MYSQL *mysqlConnection(DbConfig *dbConfigElement){

    MYSQL *mySQLConnection;

    if (mysql_library_init(0, NULL, NULL) == 0)
    {
        mySQLConnection = mysql_init(NULL);

        if (mySQLConnection != NULL)
        {
            fprintf(stdout, "[OK] mysql_init\n");

            if (mysql_real_connect(mySQLConnection,  dbConfigElement->host, dbConfigElement->user, dbConfigElement->passwd, dbConfigElement->db, 0, NULL, 0) != NULL)
            {
                fprintf(stdout, "[OK] mysql_real_connect\n");
            }
            else
            {
                fprintf(stderr, "[ERR] mysql_real_connect : '%s'\n", mysql_error(mySQLConnection));
            }
 
            /* Fermeture de la connexion / Liberation memoire mysql */
        }
        else
        {
            perror("mysql_init");
        }
    }
    else
    {
        fprintf(stderr, "[ERR] mysql_library_init\n");
    }

    return mySQLConnection;
}