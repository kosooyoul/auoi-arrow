#include <pistache/description.h>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/serializer/rapidjson.h>

#include "./App.h"
#include "./controller/AuoiController.h"
#include "../libs/mongodb/MongoDBService.h"

using namespace Pistache;

namespace Auoi {

    class AppService {

        public:
            AppService(Address addr)
                : httpEndpoint(std::make_shared<Http::Endpoint>(addr))
                , desc("Auoi API", "0.0.0")
            { }

            void init(size_t threads = 4)
            {
                auto opts = Http::Endpoint::options().threads(static_cast<int>(threads));
                httpEndpoint->init(opts);

                initializeRouter();
            }

            void start()
            {
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

        private:
            void initializeRouter() {
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

            void healthCheck(const Rest::Request&, Http::ResponseWriter response) {
                response.send(Http::Code::Ok, "OK");
            }

            std::shared_ptr<Http::Endpoint> httpEndpoint;
            Rest::Description desc;
            Rest::Router router;

            AuoiController *auoiController = new AuoiController();

    };

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
        delete App::mongoDBService;
    }

    MongoDBService * App::getMongoDBService() {
        return App::mongoDBService;
    }

    void App::start(const char *acceptIp, const unsigned int port, size_t threads) {
        Address addr(Ipv4::any(acceptIp), Port(port));

        AppService appService(addr);

        appService.init(threads);
        appService.start();
    }
}
