#pragma once

#include "Website.h"
#include <vector>
#include <iostream>

using namespace std;

class AutoComplete {
    virtual vector<string> getAutoCompleteEntries(const string& s) =0;
    virtual void addWebsite(Website website) =0;
};