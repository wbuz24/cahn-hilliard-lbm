#ifndef DOMAIN_HPP
#define DOMAIN_HPP

#include <vector>
#include <string>
#include "Node.hpp"

class Domain {
  public:
    long nX; // Number of nodes in X direction
    long nY; // Number of nodes in Y direction
    std::vector <Node *> nodes;

    std::string inputFile; // Input file name
    bool readFlag;         // Flag to indicate if the domain is read from a file

    Domain(long nX, long nY);
    ~Domain();
    void readCSV(std::vector<int>& tempDomain);
    void initialize(double refLen, double deltaX);
};

#endif // DOMAIN_HPP