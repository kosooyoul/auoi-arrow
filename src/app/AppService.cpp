#include <pistache/description.h>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/serializer/rapidjson.h>

#include "./App.h"
#include "./AppService.h"
#include "./controller/AuoiController.h"
#include "../libs/mongodb/MongoDBService.h"

using namespace Pistache;

namespace Auoi {

    AppService::AppService(Address addr)
        : httpEndpoint(std::make_shared<Http::Endpoint>(addr))
        , desc("Auoi API", "0.0.0")
        , auoiController(new AuoiController())
    { }

    AppService::~AppService() {
        delete this->auoiController;
    }

    void AppService::init(size_t threads) {
        auto opts = Http::Endpoint::options().threads(static_cast<int>(threads));
        httpEndpoint->init(opts);

        initializeRouter();
    }

    void AppService::start() {
        router.initFromDescription(desc);

        Rest::Swagger swagger(desc);
        swagger
            .uiPath("/docs")
            // .uiDirectory("/") // TODO
            .apiPath("/apis.json")
            .serializer(&Rest::Serializer::rapidJson)
            .install(router);

        httpEndpoint->setHandler(router.handler());
        httpEndpoint->serve();
    }

    void AppService::initializeRouter() {
        auto errorResponse = desc.response(Http::Code::Internal_Server_Error, "Internal Server Error #0");

        desc
            .info()
            .license("Apache", "http://www.apache.org/licenses/LICENSE-2.0");

        desc
            .route(desc.get("/health-check"))
            .bind(&AppService::healthCheck, this)
            .response(Http::Code::Ok, "OK")
            .hide();

        desc
            .schemes(Rest::Scheme::Http)
            .basePath("/v1")
            .produces(MIME(Application, Json))
            .consumes(MIME(Application, Json));

        auto versionPath = desc.path("/v1");

        versionPath
            .route(desc.get("/shortcuts"), "Create an shortcut")
            .bind(&AuoiController::createShortcut, this->auoiController)
            .produces(MIME(Application, Json))
            .consumes(MIME(Application, Json))
            .response(Http::Code::Ok, "OK")
            .response(errorResponse);

        desc
            .route(desc.get("/:hash"), "Redirect matched url by hash")
            .bind(&AuoiController::redirectUrlByHash, this->auoiController)
            .produces(MIME(Application, Json))
            .consumes(MIME(Application, Json))
            .response(Http::Code::Ok, "OK")
            .response(errorResponse);

        auto descPath = desc.path("/:hash");
        descPath.parameter<Rest::Type::String>("hash", "The hash operate on");
    }

    void AppService::healthCheck(const Rest::Request&, Http::ResponseWriter response) {
        response.send(Http::Code::Ok, "OK");
    }

};
