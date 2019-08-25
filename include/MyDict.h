#pragma once
#include <pthread.h>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
using std::pair;
using std::set;
using std::string;
using std::unordered_map;
using std::vector;

namespace wd {
class MyDict {
   public:
    static MyDict* getInstance();
    static void init();
    static void destroy();
    void start();
    vector<pair<string, int>>& getDict() { return _dict; }
    unordered_map<string, set<int>>& getIndexTable() { return _indexTable; }
    void storeIndex();

   private:
    MyDict();
    ~MyDict();
    void readDict(string path);
    void generateIndex(int idx);

   private:
    static MyDict* _pInstance;
    static pthread_once_t _once;
    vector<pair<string, int>> _dict;
    unordered_map<string, set<int>> _indexTable;
};

}  // namespace wd
