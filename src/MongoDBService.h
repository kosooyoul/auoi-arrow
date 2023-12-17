#pragma once
#include <mongoc/mongoc.h>

class MongoDBService {
    private:
        bool isConnected = false;
        mongoc_uri_t *uri;
        mongoc_client_t *client;
        mongoc_database_t *database;

        const char *uriString;
        const char *nameString;
        const char *dbNameString;

    public:
        MongoDBService();
        ~MongoDBService();
        void initialize();
        void destroy();
        void connect(const char *uriString, const char *nameString, const char *dbNameString);
        void disconnect();

        bool ping();
        bool queryTest();
};