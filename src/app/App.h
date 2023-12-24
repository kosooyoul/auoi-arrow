#pragma once

#include "../libs/mongodb/MongoDBService.h"

namespace Auoi {

    class App {

        private:
            static MongoDBService *mongoDBService;

        public:
            static void initialize();
            static void destroy();

            static MongoDBService * getMongoDBService();

            static void start(const char *acceptIp, const unsigned int port, size_t threads = 4);

    };

}
