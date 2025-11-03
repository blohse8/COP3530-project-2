#include "Website.h"
#include "AutoComplete.h"
#include "Constants.h"
#include "RedBlackTree.h"
#include <vector>
#include <iostream>
#include <algorithm>

vector<string> RedBlackTree::getAutoCompleteEntries(const string& s) {
    // get a vector of strings that represents the autocomplete entries that should be displayed
    vector<Website> websites;
    if (root) {
        extractAutocomplete(root, s, websites);
    }

    // sort list in order of visitations
    sort(websites.begin(), websites.end(),
    [](Website a, Website b) {
        if (a.getRank() != b.getRank())
            return a.getRank() < b.getRank();
        return a.getDomain() < b.getDomain();
    });
    
    // cap list at a certain number so as not to overwhelm the user with a massive list
    int loopCount = min(MAX_AUTOCOMPLETE_ENTRIES, (int)websites.size());
    vector<string> res;
    for (int i = 0; i < loopCount; i++) {
        res.push_back(websites[i].getDomain());
    }
    return res;
}

void RedBlackTree::addWebsite(Website website) {
    TreeNode* insertNode = new TreeNode{website};
    root = insert(insertNode, root);
    if (root->red) {
        root->red = false;
    }
}

void RedBlackTree::addInplace(string url, string subdomains, int rank) {
    Website website{url, subdomains, rank};
    addWebsite(website);
}

string RedBlackTree::getPostorder() {
    if (root) {
        std::string res = lengthenPostorder(root, true);
        res.pop_back();
        res.pop_back();
        return res;
    }else {
        return "";
    }
}

void RedBlackTree::clear() {
    clearRecursive(root);
    root = nullptr;
}

void RedBlackTree::extractAutocomplete(TreeNode* node, const string& s, vector<Website>& res) {
    // essentially runs an inorder traversal of the list but only includes items equal to the current search string
    string comp = node->website.getDomain().substr(0, s.size());
    if (node->left && s <= comp) {
        extractAutocomplete(node->left, s, res);
    }
    if (s == comp) {
        res.push_back(node->website);
    }
    if (node->right) {
        extractAutocomplete(node->right, s, res);
    }
}

void RedBlackTree::clearRecursive(TreeNode* node) {
    if (node->left) {
        clearRecursive(node->left);
        node->left = nullptr;
    }
    if (node->right) {
        clearRecursive(node->right);
        node->right = nullptr;
    }
    delete node;
}

string RedBlackTree::lengthenPostorder(TreeNode* node, bool url) {
    std::string res = "";
    if (node->left) {
        res += lengthenPostorder(node->left, url);
    }
    if (node->right) {
        res += lengthenPostorder(node->right, url);
    }
    std::string addition;
    if (url) {
        addition = node->website.getDomain();
    }else {
        addition = node->website.getRank();
    }
    res += addition;
    res += ", ";
    return res;
}

bool RedBlackTree::isRed(TreeNode* node) {
    if (!node) {
        return false;
    }else {
        return node->red;
    }
}

TreeNode* RedBlackTree::insert(TreeNode* insertNode, TreeNode* node) {
    if (node) {
        if (insertNode->website < node->website) {
            node->left = insert(insertNode, node->left);
            if (isRed(node->left)) {
                bool leftGrandchildRed = isRed(node->left->left);
                bool rightGrandchildRed = isRed(node->left->right);
                if (isRed(node->right) && (leftGrandchildRed || rightGrandchildRed)) {
                    //uncle is red, recolor
                    node->left->red = false;
                    node->right->red = false;
                    node->red = true;
                }else if (leftGrandchildRed) {
                    //uncle is black, LL imbalance
                    node = rotationLL(node);
                }else if (rightGrandchildRed) {
                    //uncle is black, LR imbalance
                    node = rotationLR(node);
                }
            }
        }else {
            node->right = insert(insertNode, node->right);
            if (isRed(node->right)) {
                bool leftGrandchildRed = isRed(node->right->left);
                bool rightGrandchildRed = isRed(node->right->right);
                if (isRed(node->left) && (leftGrandchildRed || rightGrandchildRed)) {
                    //uncle is red, recolor
                    node->left->red = false;
                    node->right->red = false;
                    node->red = true;
                }else if (leftGrandchildRed) {
                    //uncle is black, RL imbalance
                    node = rotationRL(node);
                }else if (rightGrandchildRed) {
                    //uncle is black, RR imbalance
                    node = rotationRR(node);
                }
            }
        }
        return node;
    }else {
        return insertNode;
    }
}

TreeNode* RedBlackTree::rotationRR(TreeNode* node) {
    TreeNode* A = node;
    TreeNode* B = A->right;
    TreeNode* temp = B->left;

    B->left = A;
    A->right = temp;

    bool tempRed = A->red;
    A->red = B->red;
    B->red = tempRed;

    return B;
}

TreeNode* RedBlackTree::rotationLR(TreeNode* node) {
    TreeNode* A = node;
    TreeNode* B = A->left;
    TreeNode* C = B->right;
    
    TreeNode* temp = C->left;
    A->left = C;
    C->left = B;
    B->right = temp;

    temp = C->right;
    C->right = A;
    A->left = temp;

    bool tempRed = A->red;
    A->red = C->red;
    C->red = tempRed;

    return C;
}

TreeNode* RedBlackTree::rotationRL(TreeNode* node) {
    TreeNode* A = node;
    TreeNode* B = A->right;
    TreeNode* C = B->left;
    
    TreeNode* temp = C->right;
    A->right = C;
    C->right = B;
    B->left = temp;

    temp = C->left;
    C->left = A;
    A->right = temp;

    bool tempRed = A->red;
    A->red = C->red;
    C->red = tempRed;

    return C;
}

TreeNode* RedBlackTree::rotationLL(TreeNode* node) {
    TreeNode* A = node;
    TreeNode* B = A->left;
    TreeNode* temp = B->right;

    B->right = A;
    A->left = temp;

    bool tempRed = A->red;
    A->red = B->red;
    B->red = tempRed;
    
    return B;
}