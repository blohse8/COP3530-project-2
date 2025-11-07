#pragma once

#include "Website.h"
#include "AutoComplete.h"
#include "Constants.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct TreeNode {
    Website website;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    bool red = true;
};

class RedBlackTree : public AutoComplete {
    public:
    TreeNode* root = nullptr;
    ~RedBlackTree() {   clear();    }
    virtual vector<string> getAutoCompleteEntries(const string& s);
    virtual void addWebsite(Website website);
    void addInplace(string url, string subdomains, int rank);
    string getPostorder();
    void clear();

    private:
    void extractAutocomplete(TreeNode* node, const string& s, vector<Website>& res);
    void clearRecursive(TreeNode* node);
    string lengthenPostorder(TreeNode* node, bool url);
    bool isRed(TreeNode* node);
    TreeNode* insert(TreeNode* insertNode, TreeNode* node);
    TreeNode* rotationRR(TreeNode* node);
    TreeNode* rotationLR(TreeNode* node);
    TreeNode* rotationRL(TreeNode* node);
    TreeNode* rotationLL(TreeNode* node);
};