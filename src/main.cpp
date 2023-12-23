#include <iostream>
#include "./app/App.h"

using namespace Auoi;

int main() {
    App::initialize();

    App::start("0.0.0.0", 60000);

    App::destroy();
}
