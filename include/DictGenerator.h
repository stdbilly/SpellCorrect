#pragma once
#include <string>
#include <map>
#include <vector>
using std::string;
using std::map;
using std::vector;

namespace wd {
class DictGenerator {
   public:
    DictGenerator();
    ~DictGenerator();
    void genetateENdict();
    void genetateCNdict();
    void storeDict();
    
    private:
    void importFiles();
   private:
    string _path;//语料库存放目录
    vector<string> _enFiles;//语料库文件存放路径集合
    vector<string> _cnFiles;
    map<string,int> _enDict;
    map<string,int> _cnDict;
};

}  // namespace wd
