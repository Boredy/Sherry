//
// Created by D@ on 11/6/18.
//

#include "hashMap.h"
#include <math.h>
using namespace std;
hashMap::hashMap(bool hash1, bool coll1) {
    mapSize = 101;
    numKeys = 0;
    c1 = coll1;
    h1 = hash1;
    first = "";
    collisionct1 = 0;
    collisionct2 = 0;
    map = new hashNode*[mapSize];
    for (int i = 0; i < mapSize; i++)
        map[i] = NULL;
}

void hashMap::addKeyValue(string k, string v) {

}

int hashMap::getIndex(string k) {
    int hashIndex;
    if (h1 == true) {
        hashIndex = calcHash(k) % mapSize;
    } else {
        hashIndex = calcHash2(k) % mapSize;
    }

    return hashIndex;
}

unsigned long hashMap::calcHash(string k) {
    unsigned long hash = 5381;
    int length = k.length();
    int c;

    for (int i = 0; i < length; i++) {
        c = (int)k[i];
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

unsigned long hashMap::calcHash2(string k) {
    unsigned long hash = 0;
    int length = k.length();
    int c;

    for (int i = 0; i < length; i++) {
        c = (int)k[i];
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

void hashMap::getClosestPrime() {
    int i = mapSize * 2 + 1;
    while (!isPrime(i)) {
        i++;
    }
    mapSize = i;

}

bool hashMap::isPrime(int x) {
    bool flag = false;
    int i = 2;
    while (i < sqrt(x)) {
        if (x % i == 0) {
            flag = true;
            break;
        } else {
            flag = false;
        }
        i++;
    }

    if (flag == false && x > 1) {
        return true;
    } else {
        return false;
    }
}
void hashMap::reHash() {
    int oldMapSize = mapSize;
    getClosestPrime();

    hashNode** tmpHashMap = new hashNode*[mapSize];
    for (int i = 0; i < mapSize; i++) {
        tmpHashMap[i] = NULL;
    }

    for (int i = 0; i < oldMapSize; i++) {
        hashNode* n = map[i];

        while (n != NULL) {
            hashNode* tmp2 = n;
            int newIndex = getIndex(tmp2->keyword);

            //check for collision and calls either collHash1 or collHash2
            if (tmpHashMap[newIndex] == NULL) {
                tmpHashMap[newIndex] = tmp2;
            } else {
                if (c1 == true) {
                    collHash1(tmpHashMap, newIndex, tmp2);
                } else {
                    collHash2(tmpHashMap, newIndex, tmp2);
                }
            }
            n = n->next;
        }
    }


}
//chaining
int hashMap::collHash1(hashNode** hmap, int i, hashNode* h) {
    hashNode* ptr = h;
    hashNode* last = hmap[i];

    while (last->next != NULL) {
        last = last->next;
    }

    last->next = ptr;
    ptr->next = NULL;
    return 0;
}
//linear probing
int hashMap::collHash2(hashNode** hmap, int i, hashNode* h) {

    return 0;
}

int hashMap::findKey(string k) {
    return -1;
}

void hashMap::printMap() {
    if (mapSize == 0) {
        cout<<"empty hashMap"<<endl;
    } else {
        for (int i = 0; i < mapSize; i++) {
            if (map[i] == NULL) {
                cout<<"Index "<<i<<" is empty"<<endl;
            } else {
                cout<<"Index "<<i<<" ";
                hashNode* ptr = map[i];
                while(ptr != NULL){
                    cout<<"key: "<<ptr->keyword<<" values: ";
                    for (int j = 0; j < ptr->currSize; j++) {
                        cout<<ptr->values[j]<<", ";
                    }
                    ptr = ptr->next;
                }
                cout<<endl;
            }
        }
    }
}

