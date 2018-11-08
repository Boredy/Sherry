#include <iostream>
#include "hashMap.h"
#include "hashNode.h"
#include <math.h>
using namespace std;
unsigned long calcHash(string k) {
    unsigned long hash = 5381;
    int length = k.length();
    int c;

    for (int i = 0; i < length; i++) {
        c = (int)k[i];
        hash = ((hash << 5) + hash) + c;
    }
    cout<<hash<<endl;
    return hash;
}
int main(int argc, char** argv) {

    calcHash("hello");
    calcHash("hell");
    calcHash("use");
    calcHash("be");
    calcHash("to");

    return 0;
}