#include "../libs/app/AppService.h"
#include "./AppRouter.h"
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

    void App::start(const char *acceptIp, const unsigned int port, size_t threads) {
        Address addr(Ipv4::any(acceptIp), Port(port));

        AppService appService(addr);
        AppRouter appRouter;

        appService.init(&appRouter, threads);
        appService.start();
    }
}
