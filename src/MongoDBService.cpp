#include "MongoDBService.h"

MongoDBService::MongoDBService() {
    this->initialize();
}

MongoDBService::~MongoDBService() {
    this->destroy();
}

void MongoDBService::initialize() {
    mongoc_init();
}

void MongoDBService::destroy() {
    this->disconnect();
    mongoc_cleanup();
}

void MongoDBService::connect(const char *uriString, const char *nameString, const char *dbNameString) {
    bson_error_t error;

    if (this->isConnected == true) return;
    this->isConnected = true;

    /*
    * Safely create a MongoDB URI object from the given string
    */
    this->uri = mongoc_uri_new_with_error(uriString, &error);
    if (!this->uri) {
        fprintf(stderr, "failed to parse URI: %s\nerror message: %s\n", uriString, error.message);
        return;
    }

    /*
    * Create a new client instance
    */
    this->client = mongoc_client_new_from_uri(this->uri);
    if (!this->client) {
        return;
    }

    /*
     * Register the application name so we can track it in the profile logs
     * on the server. This can also be done from the URI (see other examples).
     */
    mongoc_client_set_appname(this->client, nameString);

    /*
     * Get a handle on the database "db_name"
     */
    this->database = mongoc_client_get_database(this->client, dbNameString);

    this->uriString = uriString;
    this->nameString = nameString;
    this->dbNameString = dbNameString;
}

void MongoDBService::disconnect() {
    if (this->isConnected != true) return;

    mongoc_database_destroy(this->database);
    mongoc_uri_destroy(this->uri);
    mongoc_client_destroy(this->client);
    mongoc_cleanup();
}

bool MongoDBService::ping() {
    bson_t *command;
    bson_t reply;
    bson_error_t error;
    bool isSucceed;
    char *str;

    do {
        /*
        * Do work. This example pings the database, prints the result as JSON and
        * performs an insert
        */
        command = BCON_NEW("ping", BCON_INT32(1));

        isSucceed = mongoc_client_command_simple(client, "admin", command, NULL, &reply, &error);
        if (!isSucceed) {
            fprintf(stderr, "%s\n", error.message);
            break;
        }

        str = bson_as_json(&reply, NULL);
        printf("ping reply: %s\n", str);
    } while (false);

    bson_destroy(&reply);
    bson_destroy(command);
    bson_free(str);

    return isSucceed;
}

bool MongoDBService::queryTest() {
    mongoc_collection_t *collection;

    bson_t *command;
    bson_t reply;
    bson_error_t error;
    bool isSucceed;
    char *str;

    do {
        /*
        * Get a handle on the collection "coll_name"
        */
        collection = mongoc_client_get_collection(client, this->dbNameString, "logs");

        command = BCON_NEW("hello", BCON_UTF8("world"));

        isSucceed = mongoc_collection_insert_one(collection, command, NULL, &reply, &error);
        if (!isSucceed) {
            fprintf(stderr, "%s\n", error.message);
            break;
        }

        str = bson_as_json(&reply, NULL);
        printf("insert reply: %s\n", str);
    } while (false);

    bson_destroy(&reply);
    bson_destroy(command);
    bson_free(str);

    /*
     * Release our handles and clean up libmongoc
     */
    mongoc_collection_destroy(collection);

    return isSucceed;
}