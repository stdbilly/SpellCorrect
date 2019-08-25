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
    void buildIndex();
    void loadIndex();
    vector<pair<string, int>>& getEnDict() { return _enDict; }
    vector<pair<string, int>>& getCnDict() { return _cnDict; }
    unordered_map<string, set<int>>& getEnIndexTable() { return _enIndexTable; }
    unordered_map<string, set<int>>& getCnIndexTable() { return _cnIndexTable; }

   private:
    MyDict();
    ~MyDict();
    void readDict();
    size_t getCnCharLen(char ch);
    void generateEnIndex(int idx);
    void generateCnIndex(int idx);
    void storeEnIndex();
    void storeCnIndex();
    void readIndex(bool isEN);

   private:
    static MyDict* _pInstance;
    static pthread_once_t _once;
    vector<pair<string, int>> _enDict;
    vector<pair<string, int>> _cnDict;
    unordered_map<string, set<int>> _enIndexTable;
    unordered_map<string, set<int>> _cnIndexTable;
};

}  // namespace wd
