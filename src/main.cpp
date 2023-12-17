#include <pistache/endpoint.h>
#include <iostream>
#include "App.h"
#include "MongoDBService.h"

using namespace Pistache;

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
