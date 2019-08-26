#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "Configuration.h"
#include "MyDict.h"
#include "SpellCorrectServer.h"
using std::cout;
using std::endl;
using namespace wd;


int main() {
    Configuration::getInstance("/home/whb/project/SpellCorrect/conf/my.conf");
    //EchoServer server(4, 10, "192.168.5.171", 2000);
    MyDict::getInstance()->loadIndex();

    SpellCorrectServer server(std::stoi(CONFIG["threadNum"]), std::stoi(CONFIG["queSize"]), CONFIG["ip"],  std::stoi(CONFIG["port"]));
    server.start();
    return 0;
}