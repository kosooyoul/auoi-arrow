#include <iostream>

#include "./app/App.h"

#include "./libs/logger/Logger.h"

using namespace Auoi;

int main() {
    Logger::info("Server is starting...");
    App::initialize();

    Logger::info("Listen 0.0.0.0:60000");
    App::start("0.0.0.0", 60000);

    App::destroy();
}
