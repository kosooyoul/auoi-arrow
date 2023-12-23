#include <pistache/endpoint.h>
#include "./HelloController.h"
#include "../App.h"
#include "../MongoDBService.h"

using namespace Pistache;

namespace Auoi {

    void HelloController::onRequest(const Http::Request& request, Http::ResponseWriter response) {
        MongoDBService *mongoDBService = App::getMongoDBService();

        mongoDBService->ping();
        mongoDBService->queryTest();

        response.send(Http::Code::Ok, "Hello, World!");
    }

};