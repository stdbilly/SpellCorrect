#pragma once
#include "MyTask.h"
#include "net/TCPServer.h"

namespace wd {
class SpellCorrectServer {
   public:
    SpellCorrectServer(int threadNum, int queSize, const string& ip,
               unsigned short port);

    void start();

    void onConnection(const TCPConnectionPtr& conn);
    void onMessage(const TCPConnectionPtr& conn);
    void onClose(const TCPConnectionPtr& conn);

   private:
    Threadpool _threadpool;
    TCPServer _server;
};

}  // namespace wd
