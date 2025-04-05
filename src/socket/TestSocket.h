

#ifndef TESTSOCKET_H
#define TESTSOCKET_H
#include "../common/TcpServerBase.h"


class TestSocket :public TcpServerBase{
public:
    ~TestSocket() override;
    TestSocket(uint16_t port, const std::string& name, int ioLoopNum = 1): TcpServerBase(port, name, ioLoopNum) {};
protected:
    void onBeforeListen(int fd) override;

    void onAfterAccept(int fd) override;

    void onMessage(const TcpConnectionPtr &conn, MsgBuffer *buf) override;

    void onConnection(const TcpConnectionPtr &conn) override;
};



#endif //TESTSOCKET_H
