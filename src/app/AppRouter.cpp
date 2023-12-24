#include <pistache/description.h>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/serializer/rapidjson.h>

#include "./AppRouter.h"
#include "./controller/AuoiController.h"
#include "../libs/mongodb/MongoDBService.h"

using namespace Pistache;

namespace Auoi {

    AppRouter::AppRouter(): auoiController(new AuoiController()) {
        // Do nothing
    }

    AppRouter::~AppRouter() {
        delete this->auoiController;
    }

    void AppRouter::apply(Rest::Description *desc) {
        auto errorResponse = desc->response(Http::Code::Internal_Server_Error, "Internal Server Error #0");

        desc->info().license("Apache", "http://www.apache.org/licenses/LICENSE-2.0");

        desc->route(desc->get("/health-check"))
            .bind(&AppRouter::healthCheck, this)
            .response(Http::Code::Ok, "OK")
            .hide();

        desc->schemes(Rest::Scheme::Http)
            .basePath("/v1")
            .produces(MIME(Application, Json))
            .consumes(MIME(Application, Json));

        auto versionPath = desc->path("/v1");

        versionPath.route(desc->get("/shortcuts"), "Create an shortcut")
            .bind(&AuoiController::createShortcut, this->auoiController)
            .produces(MIME(Application, Json))
            .consumes(MIME(Application, Json))
            .response(Http::Code::Ok, "OK")
            .response(errorResponse);

        desc->route(desc->get("/:hash"), "Redirect matched url by hash")
            .bind(&AuoiController::redirectUrlByHash, this->auoiController)
            .produces(MIME(Application, Json))
            .consumes(MIME(Application, Json))
            .response(Http::Code::Ok, "OK")
            .response(errorResponse);

        auto descPath = desc->path("/:hash");
        descPath.parameter<Rest::Type::String>("hash", "The hash operate on");
    }

    void AppRouter::healthCheck(const Rest::Request&, Http::ResponseWriter response) {
        response.send(Http::Code::Ok, "OK");
    }

};
