#include "Configuration.h"
#include "DictGenerator.h"
using namespace wd;

int main() {
    Configuration::getInstance("../conf/data.conf");
    //display(Configuration::getInstance()->getConfigMap());
    DictGenerator dictGen;
    dictGen.genetateEnDict();
    dictGen.storeDict();
    return 0;
}