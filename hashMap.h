//
// Created by D@ on 11/6/18.
//

#ifndef HASH_MAP_HASHMAP_H
#define HASH_MAP_HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "hashNode.h"
using namespace std;

class hashMap {
    friend class makeSeuss;
    hashNode **map;
    string first;
    int numKeys;
    int mapSize;
    bool h1;
    bool c1;
    int collisionct1;
    int collisionct2;

public:
    hashMap(bool hash1, bool coll1);
    void addKeyValue(string k, string v);
    unsigned long calcHash(string k);
    unsigned long calcHash2(string k);
    void getClosestPrime();
    void reHash();
    int collHash1(hashNode** map, int i, hashNode* h);
    int collHash2(hashNode** map, int i, hashNode* h);
    int findKey(string k);
    int getIndex(string k);
    void printMap();
    bool isPrime(int x);

};
#endif //HASH_MAP_HASHMAP_H
