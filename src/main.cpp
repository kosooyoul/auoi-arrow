#include <iostream>
#include "App.h"
#include "MongoDBService.h"

using namespace Auoi;

int main() {
    App::initialize();

    App::start("0.0.0.0", 60000);

    App::destroy();
}
