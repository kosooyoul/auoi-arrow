#pragma once

#include "./controller/ArrowController.h"
#include "./controller/HealthCheckController.h"
#include "./controller/ShortcutController.h"

#include "../libs/mongodb/MongoDBService.h"

namespace Auoi {

    class App {

        private:
            static MongoDBService *mongoDBService;

            static ArrowController *arrowController;
            static HealthCheckController *healthCheckController;
            static ShortcutController *shortcutController;

        public:
            static void initialize();
            static void destroy();

            static MongoDBService * getMongoDBService();

            static void start(const char *acceptIp, const unsigned int port, size_t threads = 4);

    };

}
