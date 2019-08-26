#pragma once
#include <map>
#include <string>
#include <vector>
using std::map;
using std::string;
using std::vector;

namespace wd {
class DictGenerator {
   public:
    DictGenerator();
    ~DictGenerator();
    void start();

   private:
    void importFiles();
    void genetateENdict();
    void genetateCNdict();
    void storeDict();

   private:
    string _path;             //语料库存放目录
    vector<string> _enFiles;  //语料库文件存放路径集合
    vector<string> _cnFiles;
    map<string, int> _dict;
};

}  // namespace wd
