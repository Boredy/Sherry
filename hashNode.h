//
// Created by D@ on 11/6/18.
//

#ifndef HASH_MAP_HASHNODE_H
#define HASH_MAP_HASHNODE_H
#include <stdio.h>
#include <string>
#include <time.h>
using namespace std;
class hashNode {
public:
    friend class hashMap;
    string keyword;
    string *values;
    hashNode* next;
    int valuesSize;
    int currSize;

//remember to put back public
    hashNode();
    hashNode(string s);
    hashNode(string s, string v);
    void addValue(string v);
    void dblArray();
    string getRandValue();
};
#endif //HASH_MAP_HASHNODE_H
