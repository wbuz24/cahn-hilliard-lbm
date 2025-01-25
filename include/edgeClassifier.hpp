#ifndef EDGECLASSIFIER_HPP
#define EDGECLASSIFIER_HPP

#include "domain.hpp"

void identifyNeighbors();
void identifyEdges();
void kClosestNeighbors();
void classifyBC();
void findBoundary(Domain &domain);

#endif // EDGECLASSIFIER_HPP