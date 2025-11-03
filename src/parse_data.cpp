// Written by Landen Parke, 11.2.25

#include "parse_data.h"
#include "Website.h"
#include "vulgarity_filter.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <unordered_map>


std::unordered_map<std::string, Website> parse_data() { // Code reference: https://cppbyexample.com/parse_csv.html
    std::string file_location = "./data/202509.csv";
    std::ifstream input{file_location};
    std::unordered_map<std::string, Website> output;

    std::string line;
    std::getline(input, line); // header


    if (!input.is_open()) {
        std::cerr << "File not found: " << file_location << " does not exist\n";
        return {};
    }

    std::vector<std::string> keywords;

    for (line; std::getline(input, line);) {
        bool NSFW = false;
        for (auto word: keywords) { // Make sure link is SFW
            if (line.find(word) != std::string::npos) {
                NSFW = true;
                break;
            }
        }
        if (!NSFW) {
            int pos = line.find(',');
            std::string link = line.substr(0, pos);
            int rank = std::stoi(line.substr(pos + 1));
            int protocol_index = link.find("://");
            if (protocol_index != std::string::npos) {
                link = link.substr(protocol_index + 3);
            }
            int subdomain_index = link.find('.');
            std::string domain;
            std::string subdomain;
            if (subdomain_index != std::string::npos) {
                domain = link.substr(subdomain_index + 1);
                subdomain = link.substr(0, subdomain_index);
            } else {
                domain = link;
                subdomain = "No subdomain";
            }

            auto it = output.find(domain);
            if (it != output.end()) { // domain in hashtable
                it->second.addSubdomain(subdomain, rank);
                if (it->second.getRank() > rank) {
                    it->second.setRank(rank);
                }
            } else { // domain not in hashtable
                output.emplace(domain, Website(domain, subdomain, rank));
            }
        }
        
    }

    input.close();
    return output;
    
} 




