

#ifndef TCPSERVERBASE_H
#define TCPSERVERBASE_H
#pragma once
#include <functional>
#include <trantor/net/TcpServer.h>
#include <trantor/utils/Logger.h>
#include <trantor/net/EventLoopThread.h>
#include <string>
using namespace trantor;


class TcpServerBase {

public:
    explicit TcpServerBase(uint16_t port, const std::string& name = "TcpServer", int ioLoopNum = 1)
        : loopThread(), server(loopThread.getLoop(), InetAddress(port), name)
    {
        server.setBeforeListenSockOptCallback([this](int fd) {
            this->onBeforeListen(fd);
        });

        server.setAfterAcceptSockOptCallback([this](int fd) {
            this->onAfterAccept(fd);
        });

        server.setRecvMessageCallback([this](const TcpConnectionPtr &conn, MsgBuffer *buf) {
            this->onMessage(conn, buf);
        });

        server.setConnectionCallback([this](const TcpConnectionPtr &conn) {
            this->onConnection(conn);
        });

        server.setIoLoopNum(ioLoopNum);
    }

    virtual ~TcpServerBase() = default;

    void start() {
        Logger::setLogLevel(Logger::kTrace);
        loopThread.run();
        server.start();
        loopThread.wait();
    }

protected:

    virtual void onBeforeListen(int fd)=0;

    virtual void onAfterAccept(int fd)=0;

    virtual void onMessage(const TcpConnectionPtr &conn, MsgBuffer *buf)=0;

    virtual void onConnection(const TcpConnectionPtr &conn)=0;

protected:
    EventLoopThread loopThread;
    TcpServer server;
};



#endif //TCPSERVERBASE_H
