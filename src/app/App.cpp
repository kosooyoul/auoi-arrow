#include <pistache/endpoint.h>
#include "./App.h"
#include "./controller/HelloController.h"
#include "../libs/mongodb/MongoDBService.h"

using namespace Pistache;

namespace Auoi {

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
        delete App::mongoDBService;
    }

    MongoDBService * App::getMongoDBService() {
        return App::mongoDBService;
    }

    void App::start(const char *acceptIp, const int port) {
        Address addr(Ipv4::any(acceptIp), Port(port));

        auto opts = Http::Endpoint::options().threads(1);
        Http::Endpoint server(addr);
        server.init(opts);
        server.setHandler(Http::make_handler<HelloController>());
        server.serve();
    }
}
