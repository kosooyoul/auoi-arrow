#include "./App.h"
#include "./controller/ArrowController.h"
#include "./controller/HealthCheckController.h"
#include "./controller/ShortcutController.h"

#include "../libs/app/AppService.h"
#include "../libs/mongodb/MongoDBService.h"

using namespace Pistache;

namespace Auoi {

    MongoDBService * App::mongoDBService = NULL;

    ArrowController * App::arrowController = NULL;
    HealthCheckController * App::healthCheckController = NULL;
    ShortcutController * App::shortcutController = NULL;

    void App::initialize() {
        const char *nameString = "auoi-arrow";
        const char *dbNameString = "auoi_arrow";
        const char *uriString = "mongodb://virtual.com:27017";

        App::mongoDBService = new MongoDBService();
        App::mongoDBService->connect(uriString, nameString, dbNameString);

        App::arrowController = new ArrowController();
        App::healthCheckController = new HealthCheckController();
        App::shortcutController = new ShortcutController();
    }

    void App::destroy() {
        App::mongoDBService->destroy();
        delete App::mongoDBService;

        delete App::arrowController;
        delete App::healthCheckController;
        delete App::shortcutController;
    }

    MongoDBService * App::getMongoDBService() {
        return App::mongoDBService;
    }

    void App::start(const char *acceptIp, const unsigned int port, size_t threads) {
        AppService appService(acceptIp, port);

        appService.init(threads);

        App::arrowController->route(appService.getDescription());
        App::healthCheckController->route(appService.getDescription());
        App::shortcutController->route(appService.getDescription());

        appService.start();
    }
}
