// Written by Landen Parke, 11.2.25

#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <vector>
#include <chrono>
#include "Website.h"
#include "parse_data.h"
#include "terminal.h"
#include "Constants.h"
#include "RedBlackTree.h"
#include "Trie_tree.cpp"
#include <cmath>

// TODO: Implement autocomplete

void websiteSearch(std::string input, std::unordered_map<std::string, Website>& sites) {
    auto it = sites.find(input); 
    if (it != sites.end()) { // site exists
        auto website = it->second;
        std::vector<std::pair<std::string, int>> subdomains = website.getSubdomains();
        printFrameDash();
        // hyperlink
        std::cout << "http://";
        if (subdomains[0].first != "No subdomain") {
            std::cout << subdomains[0].first << '.';
        }
        std::cout << website.getDomain() << "\n";
        // site data
        std::cout << "Domain:   " << website.getDomain() << std::endl;
        std::cout << "Rank:     This domain is in the top " << website.getRank() << " websites." << std::endl;
        printFrameDash();
        // subdomain table
        std::cout << "Subdomains: " << std::endl;
        for (int i = 0; i < subdomains.size(); ++i) {
            std::cout << std::left << std::setw(18) << subdomains[i].first;
            std::cout << std::right << std::setw(9) << subdomains[i].second;
            std::cout << std::endl;
            if (i == 9 && subdomains.size() != 10) { // prints out 10 max
                std::cout << std::left << std::setw(18) << "...";
                std::cout << std::right << std::setw(9) << "..." << std::endl;
                std::cout << "There are " << subdomains.size() - 10 << " more subdomains." << std::endl;
                break;
            }
        }
        printFrameDash();
        std::cout << std::endl;
        printFrame();
        
    } else { // site doesnt exist
        std::cout << "No matching domain...\n";
    }
}

int main() {
    // Parse Data
    auto start = std::chrono::high_resolution_clock::now();
    std::unordered_map<std::string, Website> sites = parse_data(); // key is site domain, value is a Website class containing data on site
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "\nTime to parse data: " << duration.count() << "ms (" << std::setprecision(2)<< static_cast<float>(duration.count())/1000 << " second[s])\n" << std::endl;

    // Add data to Red-Black Tree
    auto startRBT = std::chrono::high_resolution_clock::now();
    RedBlackTree RBT_Autocomp;
    for (auto i = sites.begin(); i != sites.end(); ++i) {
        RBT_Autocomp.addWebsite(i->second); // add websites to RBT
    }
    auto stopRBT = std::chrono::high_resolution_clock::now();
    auto durationRBT = std::chrono::duration_cast<std::chrono::milliseconds>(stopRBT - startRBT);
    std::cout << "Time to add data to Red-Black Tree: " << durationRBT.count() << "ms (" << std::setprecision(2)<< static_cast<float>(durationRBT.count())/1000 << " second[s])\n" << std::endl;

    // Add data to Trie
    auto startTrie = std::chrono::high_resolution_clock::now();
    Trie Trie_Autocomp;
    for (auto i = sites.begin(); i != sites.end(); ++i) {
        Trie_Autocomp.insert_website(i->second.getDomain()); // add domains
    }
    auto stopTrie = std::chrono::high_resolution_clock::now();
    auto durationTrie = std::chrono::duration_cast<std::chrono::milliseconds>(stopTrie - startTrie);
    std::cout << "Time to add data to Trie: " << durationTrie.count() << "ms (" << std::setprecision(2)<< static_cast<float>(durationTrie.count())/1000 << " second[s])\n" << std::endl;

    std::string fastest;
    if (durationTrie.count() > durationRBT.count()) {
        fastest = "Red-Black Tree";
    } else {
        fastest = "Trie";
    }
    std::cout << "The " << fastest << " is faster by " << (std::abs(durationRBT.count() - durationTrie.count())) << "ms (" << std::setprecision(2)<< static_cast<float>(std::abs(durationRBT.count() - durationTrie.count()))/1000 << " second[s])\n\n";


    bool exitCode = false;
    printLogo();
    std::cout << "\nWelcome to WebTop!\nThis program is designed to compare the autocomplete functionality of Red-Black Trees and Tries.\n\n";

    printFrame();

    
    while (!exitCode) {
        // Red-Black Tree Autocomplete
        std::cout << "\nRed-Black Tree Autocomplete\n";
        bool validInputRBT = false;
        std::string inputRBT;
        while (!validInputRBT) {
            std::cout << "\nPlease enter at least two letters of your website domain: ";
            std::cin >> inputRBT;
            std::cout << "\n";
            if (inputRBT.length() >= 2) {
                validInputRBT = true;
            }
        }
        auto startAutoRBT = std::chrono::high_resolution_clock::now();
        std::vector<std::string> resultRBT = RBT_Autocomp.getAutoCompleteEntries(inputRBT); // return results of autocomplete (max 10)
        auto stopAutoRBT = std::chrono::high_resolution_clock::now();
        auto durationAutoRBT = std::chrono::duration_cast<std::chrono::milliseconds>(stopAutoRBT - startAutoRBT);
        std::cout << "\nTime to autocomplete with Red-Black Tree: " << durationAutoRBT.count() << "ms (" << std::setprecision(2)<< static_cast<float>(durationAutoRBT.count())/1000 << " second[s])\n" << std::endl;
        if (resultRBT.size() > 0) {
            std::cout << "Results:\n";
            validInputRBT = false;
            std::string websiteInputRBT;
            int inputChoiceRBT;
            while (!validInputRBT) {
                for (int i = 0; i < resultRBT.size(); ++i) { // print website results
                    std::cout << std::to_string(i + 1) << ".) " << resultRBT[i] << "\n";
                }   
                std::cout << "\nPlease choose a website: ";
                std::cin >> inputChoiceRBT;
                std::cout << "\n";
                if (inputChoiceRBT >= 1 && inputChoiceRBT <= resultRBT.size()) {
                    validInputRBT = true;
                    websiteInputRBT = resultRBT[inputChoiceRBT - 1];
                }
            }
            websiteSearch(websiteInputRBT, sites); // show data on site

        } else {
            std::cout << "\nNo results...\n"; // no autocomplete results
            printFrameDash();
            std::cout << std::endl;
            printFrame();
        }

        // Trie Autocomplete
        std::cout << "\nTrie Autocomplete\n";
        bool validInputTrie = false;
        std::string inputTrie;
        while (!validInputTrie) {
            std::cout << "\nPlease enter at least two letters of your website domain: ";
            std::cin >> inputTrie;
            std::cout << "\n";
            if (inputTrie.length() >= 2) {
                validInputTrie = true;
            }
        }
        if (inputTrie == "x") {
            exitCode = true;
            break;
        }
        auto startAutoTrie = std::chrono::high_resolution_clock::now();
        std::vector<std::string> resultTrie = Trie_Autocomp.autocomplete_suggest(inputTrie);
        auto stopAutoTrie = std::chrono::high_resolution_clock::now();
        auto durationAutoTrie = std::chrono::duration_cast<std::chrono::milliseconds>(stopAutoTrie- startAutoTrie);
        std::cout << "\nTime to autocomplete with Trie: " << durationAutoTrie.count() << "ms (" << std::setprecision(2)<< static_cast<float>(durationAutoTrie.count())/1000 << " second[s])\n" << std::endl;
        std::sort(resultTrie.begin(), resultTrie.end(), [&sites](std::string website1, std::string website2) { // sort the returned vector by the ranking of domain
            return sites.at(website1).getRank() < sites.at(website2).getRank();
        });
        if (resultTrie.size() > 0) {
            std::cout << "Results:\n";
            validInputTrie = false;
            std::string websiteInputTrie;
            int inputChoiceTrie;
            while (!validInputTrie) {
                for (int i = 0; i < resultTrie.size(); ++i) {
                    std::cout << std::to_string(i + 1) << ".) " << resultTrie[i] << "\n";
                    if (i == 9) {
                        break;
                    }
                }   
                std::cout << "\nPlease choose a website: ";
                std::cin >> inputChoiceTrie;
                std::cout << "\n";
                if (inputChoiceTrie >= 1 && inputChoiceTrie <= resultTrie.size()) {
                    validInputTrie = true;
                    websiteInputTrie = resultTrie[inputChoiceTrie - 1];
                }
            }
            websiteSearch(websiteInputTrie, sites);

        } else {
            std::cout << "\nNo results...\n";
            printFrameDash();
            std::cout << std::endl;
            printFrame();
        }

        std::cout << "\nSearch for websites again? (y/N): ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string loop_in;
        std::getline(std::cin, loop_in);
        if (loop_in.empty() || (loop_in != "y" && loop_in != "Y")) {
            exitCode = true;
        } else {
            exitCode = false;
        }
        std::cout << "\n";
        printFrame();
    }
    return 0;
}