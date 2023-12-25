#include <pistache/description.h>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/serializer/rapidjson.h>

#include "../../libs/logger/Logger.h"
#include "./HealthCheckController.h"

using namespace Pistache;

namespace Auoi {

    void HealthCheckController::route(Rest::Description *desc) {
        desc->route(desc->get("/health-check"))
            .bind(&HealthCheckController::healthCheck, this)
            .response(Http::Code::Ok, "OK")
            .hide();
    }

    void HealthCheckController::healthCheck(const Rest::Request&, Http::ResponseWriter response) {
        Logger::verbose("Called HealthCheckController::healthCheck");
        response.send(Http::Code::Ok, "OK");
    }

};