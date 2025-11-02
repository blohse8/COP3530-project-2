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

using namespace std;

// TODO: Implement autocomplete

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    std::unordered_map<std::string, Website> sites = parse_data();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    auto durationSec = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "Time to parse data: " << duration.count() << "ms (" << durationSec.count() << " second[s])" << std::endl;

    bool exitCode = false;

    while (!exitCode) {
        printFrame();
        printFrame();
        printLogo();
        printFrame();

        std::cout << std::endl << "Please enter a website domain (enter 'x' to exit): ";
        std::string input;
        std::cin >> input;
        if (input == "x") {
            exitCode = true;
            break;
        }
        std::cout << std::endl << std::endl;
        auto it = sites.find(input);
        if (it != sites.end()) {
            auto website = it->second;
            std::cout << "Domain:   " << website.getDomain() << std::endl;
            std::cout << "Rank:     This domain is in the top " << website.getRank() << " websites." << std::endl;
            printFrameDash();
            std::cout << "Subdomains: " << std::endl;
            std::vector<std::pair<std::string, int>> subdomains = website.getSubdomains();
            for (int i = 0; i < subdomains.size(); ++i) {
                std::cout << std::left << std::setw(18) << subdomains[i].first;
                std::cout << std::right << std::setw(9) << subdomains[i].second;
                std::cout << std::endl;
                if (i == 9 && subdomains.size() != 10) {
                    std::cout << std::left << std::setw(18) << "...";
                    std::cout << std::right << std::setw(9) << "..." << std::endl;
                    std::cout << "There are " << subdomains.size() - 10 << " more subdomains." << std::endl;
                    break;
                }
            }
            std::cout << std::endl;
            printFrame();
            std::cout << "\n\n";
            
        } else {
            std::cout << "No matching domain...\n";
        }
        



    }

    return 0;
}