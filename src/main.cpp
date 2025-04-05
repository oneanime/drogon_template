#include <iostream>

#include <drogon/drogon.h>

#include "socket/TestSocket.h"

using namespace trantor;
using namespace drogon;
int main() {

    app().loadConfigFile("../config/config.json");
    TestSocket testSocket(8888,"test",2);
    testSocket.start();  // 启动事件循环线程和服务器
    app().run();
    return 0;
}

