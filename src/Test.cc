#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "CacheManager.h"
#include "Configuration.h"
#include "MyDict.h"
#include "SpellCorrectServer.h"
using std::cout;
using std::endl;
using std::stoi;
using namespace wd;

int main() {
    Configuration::getInstance("/home/whb/project/SpellCorrect/conf/my.conf");
    MyDict::getInstance()->loadIndex();
    CacheManager::getInstance()->initCache();

    SpellCorrectServer server(stoi(CONFIG["threadNum"]),
                              stoi(CONFIG["queSize"]), CONFIG["ip"],
                              stoi(CONFIG["port"]), stoi(CONFIG["initTime"]),
                              stoi(CONFIG["periodicTime"]),
                              std::bind(&CacheManager::periodicUpdateCaches,
                                        CacheManager::getInstance()));
    server.start();
    return 0;
}