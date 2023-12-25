#include <pistache/description.h>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/serializer/rapidjson.h>

#include "./ShortcutController.h"

#include "../../libs/logger/Logger.h"
#include "../../libs/mongodb/MongoDBService.h"

using namespace Pistache;

namespace Auoi {

    void ShortcutController::route(Rest::Description *desc) {
        auto errorResponse = desc->response(Http::Code::Internal_Server_Error, "Internal Shortcut Server Error");

        desc->info().license("Apache", "http://www.apache.org/licenses/LICENSE-2.0");

        desc->schemes(Rest::Scheme::Http)
            .basePath("/v1")
            .produces(MIME(Application, Json))
            .consumes(MIME(Application, Json));

        auto versionPath = desc->path("/v1");

        versionPath.route(desc->get("/shortcuts"), "Create an shortcut")
            .bind(&ShortcutController::createShortcut, this)
            .produces(MIME(Application, Json))
            .consumes(MIME(Application, Json))
            .response(Http::Code::Ok, "OK")
            .response(errorResponse);
    }

    void ShortcutController::createShortcut(const Rest::Request& request, Http::ResponseWriter response) {
        Logger::verbose("Called ShortcutController::createShortcut");
        response.send(Http::Code::Ok, "OK");
    }

};