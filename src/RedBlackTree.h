#pragma once

#include "Website.h"
#include "AutoComplete.h"
#include <vector>
#include <iostream>

using namespace std;

class RedBlackTree : public AutoComplete {
    virtual vector<string> getAutoCompleteEntries(const string& s) {
        return {};
    }
    
    virtual void addWebsite(Website website) {
        
    }
};