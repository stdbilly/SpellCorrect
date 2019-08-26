#pragma once
#include <pthread.h>
#include <set>
#include <string>
#include <map>
#include <vector>
using std::pair;
using std::set;
using std::string;
using std::map;
using std::vector;

namespace wd {
class MyDict {
   public:
    static MyDict* getInstance();
    static void init();
    static void destroy();
    void buildIndex();
    void loadIndex();
    vector<pair<string, int>>& getDict() { return _dict; }
    map<string, set<int>>& getIndexTable() { return _indexTable; }

   private:
    MyDict();
    ~MyDict();
    void readDict(const string& path);
    size_t getBytes(char ch);
    void generateIndex(int idx);
    void storeIndex();
    void readIndex();

   private:
    static MyDict* _pInstance;
    static pthread_once_t _once;
    vector<pair<string, int>> _dict;
    map<string, set<int>> _indexTable;
};

}  // namespace wd
