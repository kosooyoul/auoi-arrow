#include <pistache/endpoint.h>
#include <iostream>
#include "MongoDBService.h"

using namespace Pistache;

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
