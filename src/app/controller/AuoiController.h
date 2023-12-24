#pragma once

#include <pistache/description.h>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/serializer/rapidjson.h>

#include "../../libs/mongodb/MongoDBService.h"

using namespace Pistache;

namespace Auoi {

    class AuoiController {

        public:
            void route(Rest::Description *desc);

            void healthCheck(const Rest::Request&, Http::ResponseWriter response);
            void createShortcut(const Rest::Request& request, Http::ResponseWriter response);
            void redirectUrlByHash(const Rest::Request& request, Http::ResponseWriter response);

    };

};