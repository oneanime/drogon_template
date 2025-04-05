

#include "TestSocket.h"

TestSocket::~TestSocket() {
}

void TestSocket::onBeforeListen(int fd) {
    LOG_DEBUG << "onBeforeListen";
}

void TestSocket::onAfterAccept(int fd) {
    LOG_DEBUG << "onAfterAccept";

}

void TestSocket::onMessage(const TcpConnectionPtr &conn, MsgBuffer *buf) {
    std::string msg(buf->peek(), buf->readableBytes());
    std::cout << "Echo: " << msg << std::endl;

    conn->send(msg.data(), msg.size());
    buf->retrieveAll();
}

void TestSocket::onConnection(const TcpConnectionPtr &conn) {
    if (conn->connected()) {
        LOG_DEBUG << "Client connected: " ;
    } else {
        LOG_DEBUG << "Client disconnected";
    }
}
