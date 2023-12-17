#include "App.h"
#include "MongoDBService.h"

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
