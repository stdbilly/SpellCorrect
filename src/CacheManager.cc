#include "CacheManager.h"
#include "Configuration.h"
//#include "threadpool/MutexLock.h"

namespace wd {
CacheManager::CacheManager()
    : _cacheNum(std::stoi(CONFIG["threadNum"])), _filepath(CONFIG["Cache"]) {
    _subCache.reserve(_cacheNum);
}

CacheManager* CacheManager::getInstance() {
    pthread_once(&_once, init);
    return _pInstance;
}

void CacheManager::init() {
    if (!_pInstance) {
        _pInstance = new CacheManager();
        ::atexit(destroy);
    }
} 

void CacheManager::destroy() {
    if (_pInstance) delete _pInstance;
}

void CacheManager::initCache() {
    Cache temp(std::stoul(CONFIG["CacheSize"]));
    temp.readFromFile(_filepath);
    for (size_t i = 0; i < _cacheNum; i++) {
        _subCache.push_back(temp);
    }
    cout << ">> read cache success" << endl;
}

void CacheManager::periodicUpdateCaches() {
    for (size_t i = 1; i < _cacheNum; ++i) {
        _subCache[0].update(_subCache[i]);
        _subCache[i].clear();
    }

    for (size_t i = 0; i < _cacheNum; i++) {
        _subCache[i].updateCache(_subCache[0]);
    }
    _subCache[0].clear();
    _subCache[0].writeToFile(_filepath);
    cout << ">> update cahces success" << endl;
}

Cache& CacheManager::getCache(size_t idx) { return _subCache[idx]; }

pthread_once_t CacheManager::_once = PTHREAD_ONCE_INIT;
CacheManager* CacheManager::_pInstance = nullptr;
}  // namespace wd
