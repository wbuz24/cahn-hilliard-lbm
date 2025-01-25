#ifndef DOMAIN_HPP
#define DOMAIN_HPP

#include <vector>
#include "json.hpp"
#include "node.hpp"
#include "constants.hpp"

// Directional offsets for neighbors
static int e[9][2] = {
    { 1,  1}, { 1,  0}, { 1, -1},
    { 0,  1}, { 0,  0}, { 0, -1},
    {-1,  1}, {-1,  0}, {-1, -1}
};

// Weights
static double w[9] = {1.0 / 36, 1.0 / 9, 1.0 / 36, 1.0 / 9, 4.0 / 9, 1.0 / 9, 1.0 / 36, 1.0 / 9, 1.0 / 36};

class Domain {
public:
    long nX;                      // Number of nodes in X direction
    long nY;                      // Number of nodes in Y direction
    int periodicity[2];           // Periodicity in X and Y directions

    std::vector<std::vector <Node *>> nodes;   // Nodes in the domain

    Domain(long nX, long nY);
    void initialize(const nlohmann::json& config, Constants &constants);
};

#endif // DOMAIN_HPP