#pragma ocne
#include <queue>
#include <set>
#include <string>
#include <vector>
#include "net/TCPServer.h"
#include "threadpool/Threadpool.h"
using std::priority_queue;
using std::set;
using std::string;
using std::vector;

namespace wd {
struct MyResult {
    string _word;
    int _frequency;
    int _distance;
};

struct MyCompare {
    bool operator()(const MyResult &lhs, const MyResult &rhs) {
        if (lhs._distance > rhs._distance) {
            return true;
        } else if (lhs._distance == rhs._distance) {
            return lhs._frequency < rhs._frequency;
        } else if (lhs._distance == rhs._distance &&
                   lhs._frequency == rhs._frequency) {
            return lhs._word < rhs._word;
        } else {
            return false;
        }
    }
};

class MyTask {
   public:
    MyTask(const string &word, const TCPConnectionPtr conn)
        : _queryWord(word), _conn(conn) {}

    void process();
    void queryIndexTable();
    void statistic(set<int> &iset);

   private:
    int distance(const string &rhs);

   private:
    string _queryWord;
    TCPConnectionPtr _conn;
    priority_queue<MyResult, vector<MyResult>, MyCompare> _resultQue;
};

}  // namespace wd
