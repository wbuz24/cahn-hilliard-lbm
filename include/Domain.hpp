#ifndef DOMAIN_HPP
#define DOMAIN_HPP

#include <vector>
#include <string>
#include "json.hpp"
#include "node.hpp"
#include "constants.hpp"

class Domain {
public:
    long nX;                      // Number of nodes in X direction
    long nY;                      // Number of nodes in Y direction
    int periodicity[2];           // Periodicity in X and Y directions

    std::vector <Node *> nodes;   // Nodes in the domain

    Domain(long nX, long nY, const nlohmann::json& config);
    void initialize(const nlohmann::json& config, Constants &constants);
};

#endif // DOMAIN_HPP