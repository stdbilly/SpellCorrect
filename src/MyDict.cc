#include "../include/MyDict.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "../include/Configuration.h"
using std::cout;
using std::endl;
using std::make_pair;

namespace wd {
MyDict* MyDict::getInstance() {
    pthread_once(&_once, init);
    return _pInstance;
}

void MyDict::init() {
    if (!_pInstance) {
        _pInstance = new MyDict();
        ::atexit(destroy);
    }
}

void MyDict::destroy() {
    if (_pInstance) delete _pInstance;
}

void MyDict::start() {
    readDict(CONFIG["Dict_en"]);
    cout << ">> read dict success" << endl;
    for (size_t idx = 0; idx != _dict.size(); ++idx) {
        generateIndex(idx);
    }
    cout << ">> generate index success" << endl;
    storeIndex();
    cout << ">> store index success" << endl;
}

void MyDict::readDict(string path) {
    std::ifstream ifs(path);
    if (!ifs) {
        perror("fopen");
        return;
    }
    string line, word;
    int frequency;
    while (getline(ifs, line)) {
        std::istringstream iss(line);
        iss >> word >> frequency;
        _dict.push_back(make_pair(word, frequency));
    }
    ifs.close();
}

void MyDict::generateIndex(int idx) {
    string key;
    string word = _dict[idx].first;
    for (size_t i = 0; i != word.size(); ++i) {
        char ch = word[i];
        key = word.substr(i, 1);
        _indexTable[key].insert(idx);
    }
}

void MyDict::storeIndex() {
    std::ofstream ofs(CONFIG["Index_en"]);
    for (auto& elem : _indexTable) {
        ofs << elem.first << " ";
        for (auto& idx : elem.second) {
            ofs << idx << " ";
        }
        ofs << endl;
    }
    ofs.close();
}

MyDict::MyDict() { cout << "MyDict()" << endl; }

MyDict::~MyDict() { cout << "~MyDict()" << endl; }

MyDict* MyDict::_pInstance = nullptr;
pthread_once_t MyDict::_once = PTHREAD_ONCE_INIT;
}  // namespace wd
