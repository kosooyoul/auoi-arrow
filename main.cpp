#include <pistache/endpoint.h>
#include <iostream>
#include <mongoc/mongoc.h>

using namespace Pistache;

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

class App {
    private:
        static MongoDBService *mongoDBService;
    public:
        static void initialize();
        static void destroy();
        static MongoDBService * getMongoDBService();
};

/*
    class App
*/
MongoDBService * App::mongoDBService = NULL;
void App::initialize() {
    const char *nameString = "auoi-arrow";
    const char *dbNameString = "auoi_arrow";
    const char *uriString = "mongodb://virtual.com:27017";

    App::mongoDBService = new MongoDBService();
    App::mongoDBService->connect(uriString, nameString, dbNameString);
}
void App::destroy() {
    App::mongoDBService->destroy();
}
MongoDBService * App::getMongoDBService() {
    return App::mongoDBService;
}

/*
    class MongoDBService
*/
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


class HelloHandler: public Http::Handler {
public:
    HTTP_PROTOTYPE(HelloHandler)

    void onRequest(const Http::Request& request, Http::ResponseWriter response) override {
        MongoDBService *mongoDBService = App::getMongoDBService();

        mongoDBService->ping();
        mongoDBService->queryTest();

        response.send(Http::Code::Ok, "Hello, World!");
    }
};

int main() {
    App::initialize();

    Address addr(Ipv4::any(), Port(8080));

    auto opts = Http::Endpoint::options().threads(1);
    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Http::make_handler<HelloHandler>());
    server.serve();
}
