#pragma once

#include <pistache/description.h>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/serializer/rapidjson.h>

#include "./AppRouter.h"

using namespace Pistache;

namespace Auoi {

    class AppService {

        private:
            std::shared_ptr<Http::Endpoint> httpEndpoint;
            Rest::Description desc;
            Rest::Router router;

        public:
            AppService(Address addr);
            ~AppService();

            void init(AppRouter *appRouter, size_t threads = 4);
            void start();

        private:
            void initializeRouter();

            void healthCheck(const Rest::Request&, Http::ResponseWriter response);

    };

}
