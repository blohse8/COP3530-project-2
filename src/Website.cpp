// Written by Landen Parke, 11.2.25

#include "Website.h"
#include <string>
#include <vector>

// Constructors

Website::Website(std::string domain, std::string sub, int rank) {
    this->domain = domain;
    this->rank_max = rank;
    subdomains.push_back(subdomain(sub, rank));
}

Website::subdomain::subdomain(std::string sub, int rank) {
    this->sub = sub;
    this->ranking = rank;
}

// Accessors
int Website::getRank() {
    return this->rank_max;
}

std::string Website::getDomain() {
    return this->domain;
}

std::vector<std::pair<std::string, int>> Website::getSubdomains() {
    std::vector<std::pair<std::string, int>> output = {};
    for (auto subd: subdomains) {
        output.push_back({subd.sub, subd.ranking});
    }
    return output;
}

// Mutators
void Website::setRank(int rank) {
    this->rank_max = rank;
}

void Website::addSubdomain(std::string sub, int rank) {
    this->subdomains.push_back(subdomain(sub, rank));
}

