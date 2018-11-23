#ifndef STRUCTURES
#define STRUCTURES


typedef struct DbConfig DbConfig;
struct DbConfig{

    char* host;
    char* user;
    char* passwd;
    char* db;


};


void initDbConfig(DbConfig *newDbConfig, char ***arrayParameters);

#endif 