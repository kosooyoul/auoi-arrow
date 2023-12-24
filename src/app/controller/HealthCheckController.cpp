#include <pistache/description.h>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/serializer/rapidjson.h>

#include "./HealthCheckController.h"

using namespace Pistache;

namespace Auoi {

    void HealthCheckController::route(Rest::Description *desc) {
        auto errorResponse = desc->response(Http::Code::Internal_Server_Error, "Internal Health Check Server Error");

        desc->info().license("Apache", "http://www.apache.org/licenses/LICENSE-2.0");

        desc->route(desc->get("/health-check"))
            .bind(&HealthCheckController::healthCheck, this)
            .response(Http::Code::Ok, "OK")
            .hide();
    }

    void HealthCheckController::healthCheck(const Rest::Request&, Http::ResponseWriter response) {
        fprintf(stderr, "healthCheck");
        response.send(Http::Code::Ok, "OK");
    }

};