#pragma once

#include <iostream>

using namespace std;

struct Website {
    string url;
    int rank;
    bool operator<(const Website& other) {
        return url < other.url;
    }
};