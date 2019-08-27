#pragma once
#include <pthread.h>
#include <memory>
#include <vector>
#include "Cache.h"
using std::shared_ptr;
using std::vector;

namespace wd {
class CacheManager {
   public:
    static CacheManager* getInstance();
    static void destroy();
    static void init();

    void initCache();
    Cache& getCache(size_t idx);
    void periodicUpdateCaches();

   private:
    CacheManager();
    ~CacheManager() {}

   private:
    static pthread_once_t _once;
    static CacheManager* _pInstance;
    int _cacheNum;  //
    string _filepath;
    vector<Cache> _subCache;  //缓存数量和线程数量一致
};

}  // namespace wd
