//
// Created by D@ on 11/6/18.
//

#include "hashMap.h"
#include <math.h>
using namespace std;
hashMap::hashMap(bool hash1, bool coll1) {
    mapSize = 5;
    numKeys = 0;
    c1 = coll1;
    h1 = hash1;
    first = "";
    collisionct1 = 0;
    collisionct2 = 0;
    map = new hashNode*[mapSize];
    for (int i = 0; i < mapSize; i++) {
        map[i] = NULL;
    }
}

void hashMap::addKeyValue(string k, string v) {
    hashNode* h = new hashNode(k,v);

    if (((double)numKeys / mapSize) >= .7) { //check for load
        reHash();
    }
    int i = getIndex(k);
    if (map[i] == NULL) {
        map[i] = h;
        numKeys++;
    } else {
        if (c1) { //handle chaining
            collHash1(map[i],h);
            numKeys++;
            collisionct1++;
        } else { //linear probing
            collHash2(i,h);
            numKeys++;
            collisionct2++;
        }
    }
}

int hashMap::getIndex(string k) {
    int hashIndex;
    if (h1)
        hashIndex = calcHash(k) % mapSize;
    else
        hashIndex = calcHash2(k) % mapSize;

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
/*
 * isPrime(int x)
 * takes in an int x
 * returns whether or not x is prime
 */
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
    hashNode** tmpMap = map;

    map = new hashNode*[mapSize];
    for (int i = 0; i < mapSize; i++) {
        map[i] = NULL;
    }
    numKeys = 0;
    collisionct1 = 0;
    collisionct2 = 0;

    for (int i = 0; i < oldMapSize; i++) {
        while (tmpMap[i] != NULL) {
            for (int j = 0; j < tmpMap[i]->currSize; j++) {
                addKeyValue(tmpMap[i]->keyword, tmpMap[i]->values[j]);
            }
            tmpMap[i] = tmpMap[i]->next;
        }
    }

    for (int i = 0; i < oldMapSize; i++)
        delete tmpMap[i];
    delete []tmpMap;
}
//chaining
void hashMap::collHash1(hashNode* i, hashNode* h) {
    if (i->next == NULL && i->keyword != h->keyword) {
        //add the node to the end of the linked list
        i->next = h;
        h->next = NULL;
        return;
    } else if (i->keyword == h->keyword) {
        //add the keyvalue
        i->addValue(h->values[0]);
        delete h;
        return;

    } else collHash1(i->next, h);
}
//linear probing
void hashMap::collHash2(int i, hashNode* h) {
    int index = i;

    while (map[index] != NULL) {
        if (index >= mapSize - 1)
            index = 0;
        else if (map[index]->keyword == h->keyword)
            break;
        index++;
    }

    if (map[index] == NULL) {
        map[index] = h;
    } else {
        map[index]->addValue(h->values[0]);
        delete h;
    }
}

int hashMap::findKey(string k) {
    bool flag = false;
    int index = getIndex(k);
    if (c1) {
        if (map[index] == NULL) {
            return -1;
        } else {
            while (map[index] != NULL) {
                if (map[index]->keyword == k) {
                    return index;
                }
                map[index] = map[index]->next;
            }
            return -1;
        }
    } else {

        if (map[index] == NULL) {
            return -1;
        } else {
            if (map[index]->keyword == k) {
                return index;
            }

            while (map[index]->keyword != k) {
                if (index >= mapSize - 1) {
                    index = 0;
                    flag = true;
                }
                if (flag == true && index == getIndex(k))
                    return -1;
                if (map[index]->keyword == k) {
                    return index;
                } else {
                    index++;
                }
            }
        }
    }
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

    cout<<collisionct1<<endl;
    cout<<collisionct2<<endl;
}

hashNode** hashMap::getMap() {
    return map;
}

