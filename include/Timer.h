#pragma once
#include <functional>
#include <iostream>
using std::cout;
using std::endl;
namespace wd {

class Timer {
   public:
    using TimerCallback = std::function<void()>;

    Timer(int initialTime, int periodicTime, TimerCallback&& cb);
    ~Timer();

    void start();
    void stop();

   private:
    int createTimerfd();
    void setTimerfd(int, int);
    void handleRead();

   private:
    int _fd;
    int _initialTime;
    int _periodicTime;
    TimerCallback _cb;
    bool _isStarted;
};

}  // end of namespace wd
