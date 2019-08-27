#include "MyTask.h"
#include <unordered_map>
#include "EditDistance.h"
#include "MyDict.h"
#include "json/json.h"
using std::unordered_map;

namespace wd {
namespace current_thread {
extern __thread int threadID;
}

//运行在线程池的某一个子线程中
void MyTask::process() {
    cout << ">> workthread " << current_thread::threadID << ": MyTask::process()"
         << endl;
    queryIndexTable();
    string result;
    if (!_resultQue.empty()) {
        Json::Value words;
        Json::FastWriter writer;
        int i = 0;
        while ((i++ < 5) && !_resultQue.empty()) {
            cout << ">> " << _resultQue.top()._word << " "
                 << _resultQue.top()._distance << " "
                 << _resultQue.top()._frequency << endl;
            string key = "候选词" + std::to_string(i);
            words[key] = _resultQue.top()._word;
            _resultQue.pop();
        }
        result = writer.write(words);
    } else {
        result = "no answer!";
    }

    _conn->sendInLoop(result);
}

void MyTask::queryIndexTable() {
    auto indexTable = MyDict::getInstance()->getIndexTable();
    set<int> iset;
    string ch;
    for (size_t idx = 0; idx != _queryWord.size();) {
        size_t nBytes = getBytes(_queryWord[idx]);
        ch = _queryWord.substr(idx, nBytes);
        idx += nBytes;
        auto it = indexTable.find(ch);
        if (it != indexTable.end()) {
            cout << "index table has character " << ch << endl;
            for (auto& i : it->second) {
                iset.insert(i);
            }
        }
    }
    statistic(iset);
}

void MyTask::statistic(set<int>& iset) {
    auto dict = MyDict::getInstance()->getDict();
    for (auto it = iset.begin(); it != iset.end(); ++it) {
        string word = dict[*it].first;
        int dist = distance(word);
        if (dist < 3) {
            MyResult res;
            res._word = word;
            res._frequency = dict[*it].second;
            res._distance = dist;
            _resultQue.push(res);
        }
    }
}

int MyTask::distance(const string& rhs) {
    return editDistance(_queryWord, rhs);
}

}  // namespace wd
