#include "../../include/DictGenerator.h"
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <fstream>
#include <iostream>
#include "../../include/Configuration.h"
#include "../../include/cppjieba/Jieba.hpp"
using std::cout;
using std::endl;

namespace wd {
DictGenerator::DictGenerator() {
    cout << "DictGenerator()" << endl;
    importFiles();
}

DictGenerator::~DictGenerator() { cout << "~DictGenerator()" << endl; }

void DictGenerator::start() {
    genetateENdict();
    genetateCNdict();
    cout << ">> generate dict success, "  << endl;
    storeDict();
} 

void DictGenerator::genetateENdict() {
    for (auto& path : _enFiles) {
        std::fstream fs(path);
        if (!fs) {
            perror("fopen");
            return;
        }

        char ch;
        while (fs >> ch) {
            if (isupper(ch)) {
                ch = tolower(ch);
                fs.seekg(-1, std::ios_base::cur);
                fs << ch;
            } else if (ispunct(ch) || isdigit(ch)) {
                fs.seekg(-1, std::ios_base::cur);
                fs << ' ';
            }
        }
        fs.clear();
        fs.seekg(0, std::ios_base::beg);
        string word;
        while (fs >> word) {
            ++_dict[word];
        }
        fs.close();
    }
}

void DictGenerator::genetateCNdict() {
    cppjieba::Jieba jieba(CONFIG["DICT_PATH"], CONFIG["HMM_PATH"],
                          CONFIG["USER_DICT_PATH"], CONFIG["IDF_PATH"],
                          CONFIG["STOP_WORD_PATH"]);

    for (auto& path : _cnFiles) {
        std::fstream fs(path);
        if (!fs) {
            perror("fopen");
            return;
        }

        char ch;
        while (fs >> ch) {
            if (ispunct(ch) || isalnum(ch) || iscntrl(ch)) {
                fs.seekg(-1, std::ios_base::cur);
                fs << ' ';
            }
        }
        fs.clear();
        fs.seekg(0, std::ios_base::beg);

        string s;
        while (fs >> s) {
            vector<string> words;
            jieba.Cut(s, words, true);
            for (auto& word : words) {
                ++_dict[word];
            }
        }
        fs.close();
    }
}

void DictGenerator::storeDict() {
    std::ofstream ofs(CONFIG["Dict"]);

    for (auto& word : _dict) {
        ofs << word.first << " " << word.second << endl;
    }

    ofs.close();
    cout << ">> store dict success" << endl;
}

void DictGenerator::importFiles() {
    string enPath = CONFIG["enLibDir"];
    string cnPath = CONFIG["cnLibDir"];
    DIR *enDir, *cnDir;
    struct dirent* pDirInfo;
    enDir = ::opendir(enPath.c_str());
    if (enDir == nullptr) {
        perror("opendir");
        return;
    }

    cnDir = ::opendir(cnPath.c_str());
    if (cnDir == nullptr) {
        perror("opendir");
        return;
    }

    while ((pDirInfo = ::readdir(enDir)) != nullptr) {
        if (*(pDirInfo->d_name) != '.') {
            _enFiles.push_back(enPath + string(pDirInfo->d_name));
        }
    }
    cout << ">> import enlish lib success" << endl;
    displayS(_enFiles);

    while ((pDirInfo = ::readdir(cnDir)) != nullptr) {
        if (*(pDirInfo->d_name) != '.') {
            _cnFiles.push_back(cnPath + string(pDirInfo->d_name));
        }
    }
    cout << ">> import Chinese lib success" << endl;
    displayS(_cnFiles);
    closedir(enDir);
    closedir(cnDir);
}
}  // namespace wd
