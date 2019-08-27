#include "Cache.h"
#include <fstream>
using std::endl;
using std::ifstream;
using std::make_pair;
using std::ofstream;

namespace wd {
Cache::Cache(size_t capacity) : _capacity(capacity) {}

Cache::Cache(const Cache& rhs) : _capacity(rhs._capacity) {
    for (auto it = rhs._cacheList.rbegin(); it != rhs._cacheList.rend(); ++it) {
        put(it->first, it->second);
    }
}

string Cache::get(const string& key) {
    if (_hashCache.find(key) == _hashCache.end()) {
        return string();
    } else {
        _cacheList.splice(_cacheList.begin(), _cacheList, _hashCache[key]);
        _hashCache[key] = _cacheList.begin();
        return _cacheList.begin()->second;
    }
}

void Cache::put(const string& key, const string& value) {
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

void Cache::updateCache(const Cache& rhs) {
    for (auto& elem : rhs._queryList) {
        put(elem.first, elem.second);
    }
}

void Cache::update(Cache& rhs) {
    for (auto& elem : rhs._queryList) {
        _queryList.push_back(make_pair(elem.first, elem.second));
    }
}

void Cache::update(const string& queryWord, const string& result) {
    _queryList.push_back(make_pair(queryWord, result));
}

void Cache::writeToFile(const string& filepath) {
    ofstream ofs(filepath);
    if (!ofs) {
        perror("fopen");
        return;
    }
    for (auto& elem : _cacheList) {
        if (elem.second.back() == '\n') {
            elem.second.erase(elem.second.size() - 1, 1);
        }
        ofs << elem.first << '\t' << elem.second << endl;
    }
    ofs.close();
}

void Cache::readFromFile(const string& filepath) {
    ifstream ifs(filepath);
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

void Cache::clear() { _queryList.clear(); }

}  // namespace wd
