#include "Timer.h"
#include <errno.h>
#include <poll.h>
#include <sys/timerfd.h>
#include <unistd.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd {

Timer::Timer(int initialTime, int periodicTime, TimerCallback&& cb)
    : _fd(createTimerfd()),
      _initialTime(initialTime),
      _periodicTime(periodicTime),
      _cb(std::move(cb)),
      _isStarted(false) {}

Timer::~Timer() {
    if (_isStarted) {
        stop();
    }
}

void Timer::start() {
    _isStarted = true;
    setTimerfd(_initialTime, _periodicTime);

    struct pollfd pfd;
    pfd.fd = _fd;
    pfd.events = POLLIN;

    while (_isStarted) {
        int nready = ::poll(&pfd, 1, 15000);
        if (nready == -1 && errno == EINTR)
            continue;
        else if (nready == -1) {
            perror(">> poll");
            return;
        } else if (nready == 0) {
            cout << ">> poll timeout!" << endl;
        } else {
            if (pfd.revents & POLLIN) {
                handleRead();    //处理事件 (水平触发)
                if (_cb) _cb();  //执行任务
            }
        }
    }
}

void Timer::stop() {
    setTimerfd(0, 0);
    _isStarted = false;
}

int Timer::createTimerfd() {
    int fd = ::timerfd_create(CLOCK_REALTIME, 0);
    if (fd == -1) {
        perror(">> timerfd_create");
    }
    return fd;
}

void Timer::setTimerfd(int initialTime, int periodicTime) {
    struct itimerspec value;
    value.it_value.tv_sec = initialTime;
    value.it_value.tv_nsec = 0;
    value.it_interval.tv_sec = periodicTime;
    value.it_interval.tv_nsec = 0;

    if (-1 == timerfd_settime(_fd, 0, &value, nullptr)) {
        perror(">> timerfd_settime");
    }
}

void Timer::handleRead() {
    uint64_t howmany;
    int ret = ::read(_fd, &howmany, sizeof(howmany));
    if (ret != sizeof(howmany)) {
        perror(">> read");
    }
}

}  // end of namespace wd
