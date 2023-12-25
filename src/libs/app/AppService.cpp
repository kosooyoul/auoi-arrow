#include <pistache/description.h>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/serializer/rapidjson.h>

#include "./AppService.h"

using namespace Pistache;

namespace Auoi
{

    AppService::AppService(const char *acceptIp, const unsigned int port):
        httpEndpoint(std::make_shared<Http::Endpoint>(Address(Ipv4::any(acceptIp), Port(port)))),
        desc("Auoi API", "0.0.0") {
        // Do nothing
    }

    AppService::~AppService() {
        // Do nothing
    }

    void AppService::init(const size_t threads) {
        auto opts = Http::Endpoint::options().threads(static_cast<int>(threads));
        httpEndpoint->init(opts);
    }

    void AppService::setLisence(const char *license, const char *url) {
        desc.info().license(license, url);
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

    Rest::Description * AppService::getDescription() {
        return &this->desc;
    }

};
