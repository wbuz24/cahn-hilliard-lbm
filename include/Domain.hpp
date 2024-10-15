#ifndef DOMAIN_HPP
#define DOMAIN_HPP

#include <vector>
#include <string>
#include "json.hpp"
#include "node.hpp"

class Domain {
public:
    long nX;                      // Number of nodes in X direction
    long nY;                      // Number of nodes in Y direction
    long nZ;                      // Number of nodes in Z direction
    int periodicity[3];           // Periodicity in X, Y, and Z directions

    bool readFlag;                // Flag to indicate if the domain is read from a file
    bool writeFlag;               // Flag to indicate if the domain is written to a file
    std::string inputFile;        // Input file name
    std::string outputFile;       // Output file name

    std::vector <Node *> nodes;   // Nodes in the domain

    Domain(long nX, long nY, long nZ, const nlohmann::json& config);
    void readCSV();
    void writeCSV();
    void initialize(double refLen, double deltaX);
    void initializeMacros(double uP, double deltaT, double deltaX);
};

#endif // DOMAIN_HPP