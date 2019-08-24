#include "DictGenerator.h"
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include "Configuration.h"

namespace wd {
DictGenerator::DictGenerator() {
    getFiles();
}

void DictGenerator::genetateEnDict() {
    for(auto& path : _enFiles) {
        std::fstream fs(path);
        if(!fs) {
            perror("fopen");
            return;
        }

        char ch;
        while (fs >> ch)
        {
            if(isupper(ch)) {
                ch = tolower(ch);
                fs.seekg(-1, std::ios_base::cur);
                fs << ch;
            } else if(ispunct(ch) || isdigit(ch)) {
                fs.seekg(-1, std::ios_base::cur);
                fs << ' ';
            }
        }
        fs.clear();
        fs.seekg(0, std::ios_base::beg);
        string word;
        while (fs >> word)
        {
            ++_enDict[word]; 
        }
        fs.close();
    }
    cout << ">> generate dict success" << endl;
} 

void DictGenerator::storeDict() {
    string enPath = Configuration::getInstance()->getConfigMap()["Dict_en"];
    std::ofstream ofs(enPath);
    if(!ofs) {
        perror("fopen");
        return;
    }

    for (auto& word : _enDict)
    {
        ofs << word.first << " " << word.second << endl;   
    }
    ofs.close();
    cout << ">> store dict success" << endl;
}

void DictGenerator::getFiles() {
    string enPath = Configuration::getInstance()->getConfigMap()["enLibDir"];
    string cnPath = Configuration::getInstance()->getConfigMap()["cnLibDir"];
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
    //displayS(_enFiles);

    while ((pDirInfo = ::readdir(cnDir)) != nullptr) {
        if (*(pDirInfo->d_name) != '.') {
            _cnFiles.push_back(cnPath + string(pDirInfo->d_name));
        }
    }
    //displayS(_cnFiles);
    cout << ">> read file success" << endl;
    closedir(enDir);
    closedir(cnDir);
}
}  // namespace wd
