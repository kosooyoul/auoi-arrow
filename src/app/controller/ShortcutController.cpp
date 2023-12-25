#include <pistache/description.h>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/serializer/rapidjson.h>

#include <iostream>
#include <functional>
#include <string>

#include <nlohmann/json.hpp>

#include "./ShortcutController.h"

#include "../../libs/logger/Logger.h"
#include "../../libs/mongodb/MongoDBService.h"
#include "../../libs/utils/Utils.h"

using namespace Pistache;

namespace Auoi {

    void ShortcutController::route(Rest::Description *desc) {
        desc->info().license("Apache", "http://www.apache.org/licenses/LICENSE-2.0");

        desc->schemes(Rest::Scheme::Http)
            .basePath("/v1")
            .produces(MIME(Application, Json))
            .consumes(MIME(Application, Json));

        auto versionPath = desc->path("/v1");

        versionPath.route(desc->post("/shortcuts"), "Create an shortcut")
            .bind(&ShortcutController::createShortcut, this)
            .produces(MIME(Application, Json))
            .consumes(MIME(Application, Json))
            .response(Http::Code::Ok, "OK")
            .response(Http::Code::Internal_Server_Error, "Internal Server Error");
    }

    void ShortcutController::createShortcut(const Rest::Request& request, Http::ResponseWriter response) {
        Logger::verbose("Called ShortcutController::createShortcut");

        try {
            auto jsonBody = nlohmann::json::parse(request.body());

            std::string url = jsonBody["url"];
            std::string hash = Utils::hash(url);

            Logger::verbose("url = %s", url.c_str());
            Logger::verbose("hash = %s", hash.c_str());

            nlohmann::json jsonData = {
                {"url", url},
                {"hash", hash}
            };
            std::string jsonString = jsonData.dump();

            response.headers().add<Http::Header::ContentType>(MIME(Application, Json));
            response.send(Http::Code::Ok, jsonString);
        } catch (const nlohmann::json::parse_error& e) {
            response.send(Http::Code::Bad_Request, "Invalid JSON format");
            return;
        }

        // std::string a = "hello2";
        // std::cout << "String: " << h << "\n";

        // std::hash<char *> hasher;
        // hasher(text);
        // std::string ab = Utils::generateUUID();
        // Logger::verbose("Called ShortcutController::uuid %s", ab.c_str());
    }

};