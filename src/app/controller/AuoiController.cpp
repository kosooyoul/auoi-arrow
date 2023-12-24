#include <pistache/description.h>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/serializer/rapidjson.h>

#include "./AuoiController.h"
#include "../App.h"
#include "../../libs/mongodb/MongoDBService.h"

using namespace Pistache;

namespace Auoi {

    void AuoiController::createShortcut(const Rest::Request& request, Http::ResponseWriter response) {
        fprintf(stderr, "createShortcut");
        response.send(Http::Code::Ok, "OK");
    }

    void AuoiController::redirectUrlByHash(const Rest::Request& request, Http::ResponseWriter response) {
        std::string hashString = request.param(":hash").as<std::string>();

        if (hashString.length() != 8 || std::regex_match(hashString, std::regex("^[0-9a-zA-Z]+$")) == false) {
            response.send(Http::Code::Bad_Request, "Invalid Hash parameter");
        }

        response.send(Http::Code::Ok, "Valid Hash parameter: " + hashString);
    }

};