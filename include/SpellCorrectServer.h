#pragma once
#include "MyTask.h"
#include "net/TCPServer.h"
#include "TimerThread.h"

namespace wd {
class SpellCorrectServer {
   public:
    using TimerCallback = Timer::TimerCallback;
    SpellCorrectServer(int threadNum, int queSize, const string& ip,
               unsigned short port,int initialTime, int periodicTime, TimerCallback&& cb);

    void start();

    void onConnection(const TCPConnectionPtr& conn);
    void onMessage(const TCPConnectionPtr& conn);
    void onClose(const TCPConnectionPtr& conn);

   private:
    Threadpool _threadpool;
    TCPServer _server;
    TimerThread _timerThread;
};

}  // namespace wd
