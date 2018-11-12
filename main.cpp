#include <iostream>
#include "hashMap.h"
#include "hashNode.h"
#include <math.h>
using namespace std;

int main(int argc, char** argv) {

    hashMap map = hashMap(true, true);

    map.addKeyValue("dog","dog");
    map.addKeyValue("tog","wombat");
    map.addKeyValue("dog", "dog");
    map.addKeyValue("asdf", "d");
    map.addKeyValue("a", "b");

    map.printMap();

    return 0;
}