#include "Cache.h"
#include <fstream>
#include "Configuration.h"
using std::ifstream;
using std::make_pair;
using std::ofstream;

namespace wd {
Cache::Cache(size_t capacity) : _capacity(capacity) {}

Cache::Cache(const Cache& rhs)
    : _capacity(rhs._capacity),
      _cacheList(rhs._cacheList),
      _hashCache(rhs._hashCache) {}

string Cache::get(const string& key) {
    if (_hashCache.find(key) == _hashCache.end()) {
        return string();
    } else {
        _cacheList.splice(_cacheList.begin(), _cacheList, _hashCache[key]);
        _hashCache[key] = _cacheList.begin();
        return _cacheList.begin()->second;
    }
}

void Cache::addElement(const string& key, const string& value) {
    if (_hashCache.find(key) != _hashCache.end()) {
        _cacheList.splice(_cacheList.begin(), _cacheList, _hashCache[key]);
        _cacheList.begin()->second = value;
        _hashCache[key] = _cacheList.begin();
    } else {
        if (_hashCache.size() == _capacity) {
            string deleteKey = _cacheList.back().first;
            _hashCache.erase(deleteKey);
            _cacheList.pop_back();
        }
        _cacheList.push_front({key, value});
        _hashCache[key] = _cacheList.begin();
    }
}

void Cache::writeToFile() {
    ofstream ofs(CONFIG["Cache"]);
    if(!ofs) {
        perror("fopen");
        return;
    }
    for (auto& elem : _cacheList)
    {
        ofs << elem.first << '\t' << elem.second << endl;    
    }
    ofs.close();
}

void Cache::readFromFile() {
    ifstream ifs(CONFIG["Cache"]);
    if (!ifs) {
        perror("fopen");
        return;
    }
    string key, value;
    while (ifs) {
        ifs >> key >> value;
        auto it = _cacheList.insert(_cacheList.end(), make_pair(key, value));
        _hashCache[key] = it;
    }
    ifs.close();
}

}  // namespace wd
