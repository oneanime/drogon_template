#include <iostream>

#include <drogon/drogon.h>
using namespace drogon;

int main() {

    app().loadConfigFile("../config/config.json").run();

    return 0;
}

