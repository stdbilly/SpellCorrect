#include "Configuration.h"
#include "DictGenerator.h"
#include "MyDict.h"
using namespace wd;

int main() {
    Configuration::getInstance("/home/whb/project/SpellCorrect/conf/my.conf");
    //display(Configuration::getInstance()->getConfigMap());
    DictGenerator dictGen;
    dictGen.genetateENdict();
    dictGen.genetateCNdict();
    dictGen.storeDict();
    MyDict::getInstance()->buildIndex();
    return 0;
}