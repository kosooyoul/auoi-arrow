#include <pistache/endpoint.h>
#include "../App.h"
#include "../../libs/mongodb/MongoDBService.h"

using namespace Pistache;

namespace Auoi {

    class HelloController: public Http::Handler {

        public:
            HTTP_PROTOTYPE(HelloController)

            void onRequest(const Http::Request& request, Http::ResponseWriter response) override ;

    };

};