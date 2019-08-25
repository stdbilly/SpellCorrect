#include "threadpool/Thread.h"
#include <iostream>
#include <string>
using std::string;

namespace wd {
namespace current_thread {
__thread const char* threadName = "wd thread";
}

struct ThreadData {
    ThreadData(const string& name, ThreadCallback&& cb)
        : _name(name), _cb(cb) {}

    void runInThread() {
        current_thread::threadName =
            (_name == string() ? "wd thread" : _name.c_str());
        if (_cb) {
            _cb();
        }
    }
    string _name;
    ThreadCallback _cb;
};

void Thread::start() {
    ThreadData* pdata = new ThreadData(_name, std::move(_cb));
    pthread_create(&_pthid, nullptr, threadFunc, pdata);
    _isRunning = true;
}

void* Thread::threadFunc(void* arg) {
    ThreadData* pdata = static_cast<ThreadData*>(arg);
    if (pdata) {
        pdata->runInThread();  //执行任务
    }
    delete pdata;
    return nullptr;
}

void Thread::join() {
    if (_isRunning) {
        pthread_join(_pthid, nullptr);
        _isRunning = false;
    }
}

Thread::~Thread() {
    if (_isRunning) {
        pthread_detach(_pthid);
    }
}

}  // namespace wd
