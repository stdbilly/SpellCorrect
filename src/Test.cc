#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "../include/TCPServer.h"
#include "../include/Threadpool.h"
using std::cout;
using std::endl;
using namespace wd;

class MyTask {
   public:
    MyTask(const string& msg, const TCPConnectionPtr conn)
        : _msg(msg), _conn(conn) {}
    //运行在线程池的某一个子线程中
    void process() {
        cout << ">> " << current_thread::threadName << ": MyTask::process()"
             << endl;
        string response = _msg;
        _conn->sendInLoop(response);
    }

   private:
    string _msg;
    TCPConnectionPtr _conn;
};

class EchoServer {
   public:
    EchoServer(int threadNum, int queSize, const string& ip,
               unsigned short port)
        : _threadpool(threadNum, queSize), _server(ip, port) {}

    void start() {
        _threadpool.start();
        _server.setConnectionCallback(
            std::bind(&EchoServer::onConnection, this, std::placeholders::_1));
        _server.setMessageCallback(
            std::bind(&EchoServer::onMessage, this, std::placeholders::_1));
        _server.setCloseCallback(
            std::bind(&EchoServer::onClose, this, std::placeholders::_1));
        _server.start();
    }

    void onConnection(const TCPConnectionPtr& conn) {
        cout << conn->toString() << " connected" << endl;
        conn->send("welcome to server");
    }

    void onMessage(const TCPConnectionPtr& conn) {
        string msg = conn->receive();
        cout << ">> client data: " << msg << endl;

        MyTask task(msg, conn);
        _threadpool.addTask(std::bind(&MyTask::process, task));
    }

    void onClose(const TCPConnectionPtr& conn) {
        cout << ">> " << conn->toString() << " disconnected" << endl;
    }

   private:
    Threadpool _threadpool;
    TCPServer _server;
};

int main() {
    EchoServer server(4, 10, "192.168.5.171", 2000);

    server.start();
    return 0;
}