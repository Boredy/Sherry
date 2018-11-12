//
// Created by D@ on 11/6/18.
//

#include "hashNode.h"
hashNode::hashNode() {
    srand(time(NULL));
    keyword = "";
    valuesSize = 0;
    currSize = 0;
    values = NULL;
    next = NULL;
}

hashNode::hashNode(string s) {
    keyword = s;
    valuesSize = 100;
    currSize = 0;
    values = new string[valuesSize];
    next = NULL;

}

hashNode::hashNode(string s, string v) {
    keyword = s;
    valuesSize = 100;
    currSize = 1;
    values = new string[valuesSize];
    values[0] = v;
    next = NULL;
}

void hashNode::addValue(string v) {
    if (currSize == valuesSize) {
        dblArray();
    }
    currSize++;
    values[currSize - 1] = v;
}

void hashNode::dblArray() {
    valuesSize = valuesSize * 2;
    string* arr = new string[valuesSize];
    for (int i = 0; i < valuesSize; i++) {
        values[i] = arr[i];
    }
    values = arr;
    delete []arr;
}

string hashNode::getRandValue() {

    if (currSize == 0) {
        return "";
    } else {
        return values[rand() % currSize];
    }
}