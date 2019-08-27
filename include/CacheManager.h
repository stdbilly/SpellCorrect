#include "Cache.h"
#include <vector>
#include <memory>
using std::vector;
using std::shared_ptr;

namespace wd {
class CacheManager {
   public:
    CacheManager(/* args */);
    ~CacheManager();

   private:
    int cacheNum;//
    vector<Cache> _subCache;
    shared_ptr<Cache> _pCache;//原缓存
};

CacheManager::CacheManager(/* args */) {}

CacheManager::~CacheManager() {}

}  // namespace wd
