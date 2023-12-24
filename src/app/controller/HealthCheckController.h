#pragma once

#include <pistache/description.h>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/serializer/rapidjson.h>

using namespace Pistache;

namespace Auoi {

    class HealthCheckController {

        public:
            void route(Rest::Description *desc);

            void healthCheck(const Rest::Request&, Http::ResponseWriter response);

    };

};