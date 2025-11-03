// Written by Landen Parke, 11.2.25

#ifndef WEBSITE_H
#define WEBSITE_H

#include <vector>
#include <string>

class Website {
    private:
    struct subdomain {
        std::string sub;
        int ranking;
        subdomain(std::string sub, int rank);
    };
    std::vector<subdomain> subdomains = {};
    std::string domain;
    int rank_max;

    public:
    Website(std::string domain, std::string sub, int rank);
    // Accessors
    int getRank();
    std::string getDomain();
    std::vector<std::pair<std::string, int>> getSubdomains();
    // Mutators
    void setRank(int rank);
    void addSubdomain(std::string sub, int rank);
    bool operator<(Website other);
};

# endif