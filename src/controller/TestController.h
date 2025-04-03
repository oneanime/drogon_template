
#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H
#pragma once
#include <drogon/HttpSimpleController.h>
using namespace drogon;


class TestController : public drogon::HttpSimpleController<TestController>{
public:

    TestController();

    void asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    //list path definitions here;
    PATH_ADD("/json", Get);
    PATH_LIST_END
};



#endif //TESTCONTROLLER_H
