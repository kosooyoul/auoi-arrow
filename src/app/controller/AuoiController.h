#include <pistache/description.h>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/serializer/rapidjson.h>
#include "../App.h"
#include "../../libs/mongodb/MongoDBService.h"

using namespace Pistache;

namespace Auoi {

    class AuoiController {

        public:
            void createShortcut(const Rest::Request& request, Http::ResponseWriter response);
            void redirectUrlByHash(const Rest::Request& request, Http::ResponseWriter response);

    };

};