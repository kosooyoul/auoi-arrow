#pragma once

#include <pistache/description.h>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/serializer/rapidjson.h>

using namespace Pistache;

namespace Auoi {

    class ShortcutController {

        public:
            void route(Rest::Description *desc);

            void createShortcut(const Rest::Request& request, Http::ResponseWriter response);

    };

};