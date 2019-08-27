#include "SpellCorrectServer.h"
using std::placeholders::_1;

namespace wd
{
    SpellCorrectServer::SpellCorrectServer(int threadNum, int queSize, const string& ip,
               unsigned short port,int initialTime, int periodicTime, TimerCallback&& cb)
        : _threadpool(threadNum, queSize), 
          _server(ip, port),
          _timerThread(initialTime, periodicTime, std::move(cb)) {}

    void SpellCorrectServer::start() {
        _threadpool.start();
        _timerThread.start();
        _server.setConnectionCallback(
            std::bind(&SpellCorrectServer::onConnection, this, _1));
        _server.setMessageCallback(
            std::bind(&SpellCorrectServer::onMessage, this, _1));
        _server.setCloseCallback(
            std::bind(&SpellCorrectServer::onClose, this, _1));
        _server.start();
    }

    void SpellCorrectServer::onConnection(const TCPConnectionPtr& conn) {
        cout << conn->toString() << " connected" << endl;
        conn->send("welcome to server");
    }

    void SpellCorrectServer::onMessage(const TCPConnectionPtr& conn) {
        string msg = conn->receive();
        if(msg.back() == '\n') {
            msg.erase(msg.size()-1, 1);
        }
        cout << ">> receive from client: " << msg << endl;

        MyTask task(msg, conn);
        _threadpool.addTask(std::bind(&MyTask::process, task));
    }

    void SpellCorrectServer::onClose(const TCPConnectionPtr& conn) {
        cout << ">> " << conn->toString() << " disconnected" << endl;
    }
    
} // namespace wd
