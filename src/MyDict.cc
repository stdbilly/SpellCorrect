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

void MyDict::buildIndex() {
    readDict(CONFIG["Dict"]);
    cout << ">> read dict success" << endl;

    for (size_t idx = 0; idx != _dict.size(); ++idx) {
        generateIndex(idx);
    }
    cout << ">> generate index success" << endl;
    storeIndex();
}

void MyDict::loadIndex() {
    readDict(CONFIG["Dict"]);
    cout << ">> load dict success" << endl;
    readIndex();
    cout << ">> load index success" << endl;
}

void MyDict::readDict(const string& path) {
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
    for (size_t i = 0; i != word.size();) {
        size_t nBytes = getBytes(word[i]);
        key = word.substr(i, nBytes);
        i += nBytes;
        _indexTable[key].insert(idx);
    }
}

size_t MyDict::getBytes(char ch) {
    if (ch & (1 << 7)) {
        size_t bytes = 1;
        for (int idx = 0; idx != 6; ++idx) {
            if (ch & (1 << (6 - idx))) {
                ++bytes;
            } else {
                break;
            }
        }
        return bytes;
    }
    return 1;
}

void MyDict::storeIndex() {
    std::ofstream ofs(CONFIG["Index"]);
    for (auto& elem : _indexTable) {
        ofs << elem.first << " ";
        for (auto& idx : elem.second) {
            ofs << idx << " ";
        }
        ofs << endl;
    }
    cout << ">> store index success" << endl;
    ofs.close();
}

void MyDict::readIndex() {
    std::ifstream ifs(CONFIG["Index"]);
    if (!ifs) {
        perror("fopen");
        return;
    }
    string line;
    while (getline(ifs, line)) {
        std::istringstream iss(line);
        string key;
        int idx;
        iss >> key;
        while (iss >> idx) {
                _indexTable[key].insert(idx);
        }
    }
    ifs.close();
}

MyDict::MyDict() { cout << "MyDict()" << endl; }

MyDict::~MyDict() { cout << "~MyDict()" << endl; }

MyDict* MyDict::_pInstance = nullptr;
pthread_once_t MyDict::_once = PTHREAD_ONCE_INIT;
}  // namespace wd
