#pragma once

#include <pistache/description.h>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/serializer/rapidjson.h>

using namespace Pistache;

namespace Auoi {

    class AppService {

        private:
            std::shared_ptr<Http::Endpoint> httpEndpoint;
            Rest::Description desc;
            Rest::Router router;

        public:
            AppService(const char *acceptIp, const unsigned int port);
            ~AppService();

            void init(const size_t threads = 4);
            void setLisence(const char *license, const char *url);

            void start();

            Rest::Description * getDescription();

    };

}
