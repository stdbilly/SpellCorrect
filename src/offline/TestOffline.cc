#include "../../include/Configuration.h"
#include "../../include/DictGenerator.h"
#include "../../include/MyDict.h"
using namespace wd;

int main() {
    Configuration::getInstance("/home/whb/project/SpellCorrect/conf/my.conf");
    //display(Configuration::getInstance()->getConfigMap());
    DictGenerator dictGen;
    dictGen.start();
    MyDict::getInstance()->buildIndex();
    return 0;
}