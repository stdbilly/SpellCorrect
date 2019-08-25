#include "MyDict.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Configuration.h"
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
    readDict();
    cout << ">> read dict success" << endl;
    for (size_t idx = 0; idx != _enDict.size(); ++idx) {
        generateEnIndex(idx);
    }
    cout << ">> generate EN index success" << endl;

    for (size_t idx = 0; idx != _cnDict.size(); ++idx) {
        generateCnIndex(idx);
    }
    cout << ">> generate CN index success" << endl;
    storeEnIndex();
    storeCnIndex();
}

void MyDict::loadIndex() {
    readDict();
    cout << ">> load dict success" << endl;
    readIndex(true);
    cout << ">> load EN index success" << endl;
    readIndex(false);
    cout << ">> load CN index success" << endl;
}

void MyDict::readDict() {
    std::ifstream ifs(CONFIG["Dict_en"]);
    if (!ifs) {
        perror("fopen");
        return;
    }
    string line, word;
    int frequency;
    while (getline(ifs, line)) {
        std::istringstream iss(line);
        iss >> word >> frequency;
        _enDict.push_back(make_pair(word, frequency));
    }
    ifs.close();

    ifs.open(CONFIG["Dict_cn"]);
    if (!ifs) {
        perror("fopen");
        return;
    }
    while (getline(ifs, line)) {
        std::istringstream iss(line);
        iss >> word >> frequency;
        _cnDict.push_back(make_pair(word, frequency));
    }
    ifs.close();
}

void MyDict::generateEnIndex(int idx) {
    string key;
    string word = _enDict[idx].first;
    for (size_t i = 0; i != word.size(); ++i) {
        key = word.substr(i, 1);
        _enIndexTable[key].insert(idx);
    }
}

void MyDict::generateCnIndex(int idx) {
    string key;
    string word = _cnDict[idx].first;
    for (size_t i = 0; i != word.size();) {
        size_t len = getCnCharLen(word[i]);
        key = word.substr(i, len);
        i += len;
        _cnIndexTable[key].insert(idx);
    }
}

size_t MyDict::getCnCharLen(char ch) {
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

void MyDict::storeEnIndex() {
    std::ofstream ofs(CONFIG["Index_en"]);
    for (auto& elem : _enIndexTable) {
        ofs << elem.first << " ";
        for (auto& idx : elem.second) {
            ofs << idx << " ";
        }
        ofs << endl;
    }
    cout << ">> store EN index success" << endl;
    ofs.close();
}

void MyDict::storeCnIndex() {
    std::ofstream ofs(CONFIG["Index_cn"]);
    for (auto& elem : _cnIndexTable) {
        ofs << elem.first << " ";
        for (auto& idx : elem.second) {
            ofs << idx << " ";
        }
        ofs << endl;
    }
    cout << ">> store CN index success" << endl;
    ofs.close();
}

void MyDict::readIndex(bool isEn) {
    std::ifstream ifs;
    if (isEn) {
        ifs.open(CONFIG["Index_en"]);
    } else {
        ifs.open(CONFIG["Index_cn"]);
    }
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
            if (isEn) {
                _enIndexTable[key].insert(idx);
            } else {
                _cnIndexTable[key].insert(idx);
            }
        }
    }
    ifs.close();
}

MyDict::MyDict() { cout << "MyDict()" << endl; }

MyDict::~MyDict() { cout << "~MyDict()" << endl; }

MyDict* MyDict::_pInstance = nullptr;
pthread_once_t MyDict::_once = PTHREAD_ONCE_INIT;
}  // namespace wd
