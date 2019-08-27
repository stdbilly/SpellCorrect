#include "threadpool/Thread.h"
#include "Timer.h"

namespace wd {

class TimerThread {
   public:
    using TimerCallback = Timer::TimerCallback;
    TimerThread(int, int, TimerCallback&& cb);

    void start();
    void stop();

   private:
    Timer _timer;
    Thread _thread;
};

}  // end of namespace wd
