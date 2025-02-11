#ifndef EDGECLASSIFIER_HPP
#define EDGECLASSIFIER_HPP

#include "domain.hpp"

std::vector<Node*> identifyNeighbors(Domain &domain, Node* node);
void identifyEdges(Domain &domain);
double euclideanDistance(Node* node1, Node* node2);
void kClosestNeighbors(Domain &domain, Node* node, int k);
void classifyBC(Domain &domain);

#endif // EDGECLASSIFIER_HPP