#pragma once
#include "MongoDBService.h"

class App {
    private:
        static MongoDBService *mongoDBService;
    public:
        static void initialize();
        static void destroy();
        static MongoDBService * getMongoDBService();
};
