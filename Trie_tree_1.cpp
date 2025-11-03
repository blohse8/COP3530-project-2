#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct TrieNode {
    map<char, TrieNode*> children;

    bool website_search =false;

    TrieNode() : website_search(false) {}
};

class Trie {

private:
    TrieNode* root;

    void collect_website(TrieNode* node, string currentWord, vector<string>& results) {
        if (node == nullptr || results.size() >= 10) {
            return;
        }

        if (node->website_search) {
            results.push_back(currentWord);
        }

        for (auto const& [key, child] : node->children) {
            if (results.size() >= 10) {
                return;
            }
            collect_website(child, currentWord + key, results);
        }
    }

    TrieNode* prefix_website_starter(const string& prefix) {
        TrieNode* current = root;
        for (char ch : prefix) {

            if (current->children.find(ch) == current->children.end()) {
                return nullptr;
            }
            current = current->children[ch];
        }
        return current;
    }

    void clear(TrieNode* node) {
        if (node == nullptr) return;
        for (auto const& [key, child] : node->children) {
            clear(child);
        }
        delete node;
    }

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        clear(root);
    }

    void insert_website(const string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->website_search = true;
    }

    vector<string> autocomplete_suggest(const string& prefix) {
        vector<string> results;

        TrieNode* startNode = prefix_website_starter(prefix);

        if (startNode == nullptr) {
            return results;
        }

        collect_website(startNode, prefix, results);

        return results;
    }
};

