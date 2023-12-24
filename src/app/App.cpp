#include "./App.h"
#include "./controller/AuoiController.h"

#include "../libs/app/AppService.h"
#include "../libs/mongodb/MongoDBService.h"

using namespace Pistache;

namespace Auoi {

    MongoDBService * App::mongoDBService = NULL;

    AuoiController * App::auoiController = NULL;

    void App::initialize() {
        const char *nameString = "auoi-arrow";
        const char *dbNameString = "auoi_arrow";
        const char *uriString = "mongodb://virtual.com:27017";

        App::mongoDBService = new MongoDBService();
        App::mongoDBService->connect(uriString, nameString, dbNameString);

        App::auoiController = new AuoiController();
    }

    void App::destroy() {
        App::mongoDBService->destroy();
        delete App::mongoDBService;
    }

    MongoDBService * App::getMongoDBService() {
        return App::mongoDBService;
    }

    void App::start(const char *acceptIp, const unsigned int port, size_t threads) {
        AppService appService(acceptIp, port);

        appService.init(threads);

        App::auoiController->route(appService.getDescription());

        appService.start();
    }
}
