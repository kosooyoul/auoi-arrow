#pragma once
#include "MongoDBService.h"

namespace Auoi {

    class App {

        private:
            static MongoDBService *mongoDBService;

        public:
            static void initialize();
            static void destroy();
            static MongoDBService * getMongoDBService();

    };

}