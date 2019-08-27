#pragma once
#include <list>
#include <string>
#include <unordered_map>
using std::list;
using std::pair;
using std::string;
using std::unordered_map;

namespace wd {
class Cache {
   public:
    using pairStrList = list<pair<string, string>>;
    Cache(size_t capacity);
    Cache(const Cache& rhs);

    string get(const string& queryWord);
    void put(const string& queryWord, const string& result);
    void readFromFile(const string& filepath);
    void writeToFile(const string& filepath);
    void update(const string& queryWord, const string& result);//更新热数据
    void update(Cache& rhs);//更新热数据
    void clear();//清空热数据
    void updateCache(const Cache& rhs);
    

   private:
    size_t _capacity;
    pairStrList _cacheList;
    unordered_map<string, pairStrList::iterator> _hashCache;
    pairStrList _queryList; //热数据
};

};  // namespace wd
