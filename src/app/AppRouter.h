#pragma once

#include <pistache/description.h>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/serializer/rapidjson.h>

#include "./controller/AuoiController.h"

using namespace Pistache;

namespace Auoi {

    class AppRouter {

        private:
            AuoiController *auoiController;

        public:
            AppRouter();
            ~AppRouter();

            void apply(Rest::Description *desc);

        private:
            void healthCheck(const Rest::Request&, Http::ResponseWriter response);

    };

}
