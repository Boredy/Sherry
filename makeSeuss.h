//
// Created by D@ on 11/6/18.
//

#ifndef HASH_MAP_MAKESEUSS_H
#define HASH_MAP_MAKESEUSS_H

#include "hashMap.h"
using namespace std;

class makeSeuss {
    hashMap *ht;
    string fn;
    string newfile;

public:
    makeSeuss(string file, string newf, bool h1, bool c1);
    void readFile();
    void writeFile();

};
#endif //HASH_MAP_MAKESEUSS_H
