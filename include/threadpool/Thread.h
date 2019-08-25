#pragma once
#include <pthread.h>
#include <functional>
#include <iostream>
#include <string>
#include "Nocopyble.h"
using std::cout;
using std::endl;
using std::string;

namespace wd {
namespace current_thread {
extern __thread const char* threadName;
}

using ThreadCallback = std::function<void()>;

class Thread : Nocopyble {
   public:
    Thread(ThreadCallback&& cb, const string& name = string())
        : _pthid(0), _isRunning(false), _cb(std::move(cb)), _name(name) {}

    ~Thread();
    void start();
    void join();
    string name() const { return _name; }
    static void* threadFunc(void*);

   private:
    pthread_t _pthid;
    bool _isRunning;
    ThreadCallback _cb;
    string _name;
};
}  // namespace wd
