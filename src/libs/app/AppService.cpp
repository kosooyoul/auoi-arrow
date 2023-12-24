#include <pistache/description.h>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/serializer/rapidjson.h>

#include "./AppService.h"
#include "./AppRouter.h"

using namespace Pistache;

namespace Auoi {

    AppService::AppService(Address addr): httpEndpoint(std::make_shared<Http::Endpoint>(addr)), desc("Auoi API", "0.0.0") {
        // Do nothing
    }

    AppService::~AppService() {
        // Do nothing
    }

    void AppService::init(AppRouter *appRouter, size_t threads) {
        auto opts = Http::Endpoint::options().threads(static_cast<int>(threads));
        httpEndpoint->init(opts);

        appRouter->apply(&desc);
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

};
