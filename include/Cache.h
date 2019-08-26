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
    void addElement(const string& queryWord, const string& result);
    void readFromFile();
    void writeToFile();

   private:
    size_t _capacity;
    pairStrList _cacheList;
    unordered_map<string, pairStrList::iterator> _hashCache;
};

};  // namespace wd
