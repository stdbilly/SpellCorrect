#include "TimerThread.h"
#include <iostream>
using std::cout;
using std::endl;

namespace wd {

TimerThread::TimerThread(int initialTime, int periodicTime, TimerCallback&& cb)
    : _timer(initialTime, periodicTime, std::move(cb)),
      _thread(std::bind(&Timer::start, &_timer), -1) {}

void TimerThread::start() { _thread.start(); }

void TimerThread::stop() {
    _timer.stop();
    _thread.join();
}

}  // end of namespace wd
