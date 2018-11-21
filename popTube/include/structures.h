#ifndef STRUCTURES
#define STRUCTURES

typedef struct DbConfig{

    char *host;
    char *user;
    char *passwd;
    char *db;


}DbConfig;


void initDbConfig(DbConfig *newDbConfig, char ***arrayParameters);

#endif 