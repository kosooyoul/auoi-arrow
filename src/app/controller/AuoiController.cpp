#include <pistache/description.h>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/serializer/rapidjson.h>

#include "./AuoiController.h"

#include "../../libs/mongodb/MongoDBService.h"

using namespace Pistache;

namespace Auoi {

    void AuoiController::route(Rest::Description *desc) {
        auto errorResponse = desc->response(Http::Code::Internal_Server_Error, "Internal Server Error #0");

        desc->info().license("Apache", "http://www.apache.org/licenses/LICENSE-2.0");

        desc->route(desc->get("/health-check"))
            .bind(&AuoiController::healthCheck, this)
            .response(Http::Code::Ok, "OK")
            .hide();

        desc->schemes(Rest::Scheme::Http)
            .basePath("/v1")
            .produces(MIME(Application, Json))
            .consumes(MIME(Application, Json));

        auto versionPath = desc->path("/v1");

        versionPath.route(desc->get("/shortcuts"), "Create an shortcut")
            .bind(&AuoiController::createShortcut, this)
            .produces(MIME(Application, Json))
            .consumes(MIME(Application, Json))
            .response(Http::Code::Ok, "OK")
            .response(errorResponse);

        desc->route(desc->get("/:hash"), "Redirect matched url by hash")
            .bind(&AuoiController::redirectUrlByHash, this)
            .produces(MIME(Application, Json))
            .consumes(MIME(Application, Json))
            .response(Http::Code::Ok, "OK")
            .response(errorResponse);

        auto descPath = desc->path("/:hash");
        descPath.parameter<Rest::Type::String>("hash", "The hash operate on");
    }

    void AuoiController::healthCheck(const Rest::Request&, Http::ResponseWriter response) {
        fprintf(stderr, "healthCheck");
        response.send(Http::Code::Ok, "OK");
    }

    void AuoiController::createShortcut(const Rest::Request& request, Http::ResponseWriter response) {
        fprintf(stderr, "createShortcut");
        response.send(Http::Code::Ok, "OK");
    }

    void AuoiController::redirectUrlByHash(const Rest::Request& request, Http::ResponseWriter response) {
        std::string hashString = request.param(":hash").as<std::string>();

        fprintf(stderr, "redirectUrlByHash");

        if (hashString.length() != 8 || std::regex_match(hashString, std::regex("^[0-9a-zA-Z]+$")) == false) {
            response.send(Http::Code::Bad_Request, "Invalid Hash parameter");
        }

        response.send(Http::Code::Ok, "Valid Hash parameter: " + hashString);
    }

};